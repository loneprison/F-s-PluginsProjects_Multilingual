"""Read-only inventory of NF source text definitions and UI consumption sites."""

from __future__ import annotations

import argparse
import re
import xml.etree.ElementTree as ET
from pathlib import Path

import tree_sitter_cpp
from tree_sitter import Language, Parser


_CPP_LANGUAGE = Language(tree_sitter_cpp.language())


def walk(node):
    yield node
    for child in node.named_children:
        yield from walk(child)


def survey(root: Path) -> str:
    parser = Parser(_CPP_LANGUAGE)
    rows = []
    details = []
    for folder in ET.parse(root / "NF-PluginsProjects.slnx").iter("Folder"):
        category = folder.attrib["Name"].strip("/")
        for project in folder.findall("Project"):
            project_path = root / project.attrib["Path"].replace("\\", "/")
            if category == "_Support":
                continue
            definitions = []
            uses = []
            for path in sorted(project_path.parent.parent.iterdir()):
                if path.suffix.lower() not in {".h", ".cpp", ".c"}:
                    continue
                source = path.read_bytes()
                source.decode("utf-8-sig", errors="strict")
                tree = parser.parse(source)
                relative = path.relative_to(root).as_posix()
                for node in walk(tree.root_node):
                    if node.type not in {"preproc_def", "call_expression"}:
                        continue
                    line = source.count(b"\n", 0, node.start_byte) + 1
                    location = f"{relative}:{line}"
                    if node.type == "preproc_def":
                        name = node.child_by_field_name("name")
                        value = node.child_by_field_name("value")
                        if name is None or value is None:
                            continue
                        key = source[name.start_byte:name.end_byte].decode("utf-8")
                        text = source[value.start_byte:value.end_byte].decode("utf-8").strip()
                        if key.startswith(("STR_", "L10N_")) or key == "NF_DESCRIPTION":
                            if '"' in text:
                                definitions.append((key, text, location))
                    elif node.type == "call_expression":
                        function = node.child_by_field_name("function")
                        arguments = node.child_by_field_name("arguments")
                        if function is None or arguments is None:
                            continue
                        name = source[function.start_byte:function.end_byte].decode("utf-8")
                        if re.search(r"(?:[.>]Add\w+|(?:PF_ADD_\w+|SaveFileDialogWithCheck|OpenFileDialog|PF_SPRINTF|About))$", name):
                            args = source[arguments.start_byte:arguments.end_byte].decode("utf-8")
                            uses.append((name, " ".join(args.split()), location))
            name = project_path.stem
            rows.append(f"| {name} | {category} | {len(definitions)} | {len(uses)} |")
            details.append(f"\n## {name}\n\n工程：`{project.attrib['Path']}`；类别：`{category}`。\n")
            details.append("\n| 文本宏 | 源码表达式 | 位置 |\n| --- | --- | --- |")
            for key, value, location in definitions:
                escaped = value.replace("|", "\\|").replace("\n", " ")
                details.append(f"| `{key}` | `{escaped}` | `{location}` |")
            details.append("\n消费位置（包含参数设置、About 和特殊对话框）：\n")
            for function, arguments, location in uses:
                details.append(f"- `{location}`：`{function}{arguments}`")
    return "\n".join([
        "# NF 文本入口调查", "", "2026-09-18；按当前解决方案逐项读取 45 个 NF 工程与 3 个开发工程。",
        "使用 Tree-sitter 排除注释节点，收集工程源目录一级 C/C++ 文件中的文本宏及 UI 消费调用。",
        "这是接入前调查，不等于预处理后的完整可见字符串清单；条件分支、未使用宏及部分模板定义仍需逐项判断。",
        "共享库入口与字节约束见 `nf-text-contract.md`。原文按源码记录，不自动等同于英语或日语。", "",
        "| 工程 | 现有类别 | 文本宏定义 | UI 调用位置 |", "| --- | --- | ---: | ---: |",
        *rows, *details, "",
    ])


def main() -> None:
    arguments = argparse.ArgumentParser()
    arguments.add_argument("--root", type=Path, default=Path.cwd())
    arguments.add_argument("--output", type=Path, required=True)
    options = arguments.parse_args()
    options.output.write_text(survey(options.root.resolve()), encoding="utf-8")


if __name__ == "__main__":
    main()
