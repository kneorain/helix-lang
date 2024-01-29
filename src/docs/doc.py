from rich.markdown import Markdown
from rich.console import Console
from rich.style import Style
from src.global_vars import HelixSyntaxHighlightingLexer, lexer, highlight_code, formatter

console = Console()

def doc(doc_id: str):
    # 01.E20 example
    # doc_id = "01.E20"
    # that goes to __file__ dir/01/E20.md
    import os
    terminal_width = os.get_terminal_size().columns
    from pathlib import Path
    doc_path = os.path.dirname(__file__) + os.sep + doc_id.replace(".", os.sep) + ".md"
    print(doc_id)
    
    if not os.path.exists(doc_path):
        console.print(f"[bold red]Error:[/bold red] Could not find documentation for [bold]{doc_id}[/bold]")
        exit(1)

    md_file = open(doc_path, "r").read()
    from rich.panel import Panel
    special_style = Style(bgcolor="default")
    
    sections_with_code: list[tuple[int, int]] = []
    in_code_block: bool = False
    for index, line in enumerate(md_file.split("\n")):
        if line.startswith("```"):
            if in_code_block:
                sections_with_code.append((start, index))
                in_code_block = False
            else:
                start = index
                in_code_block = True
    
    from rich.markdown import CodeBlock
    from rich.syntax import Syntax
    
    
    md = Panel(Markdown(md_file, inline_code_lexer=lexer, style=special_style, inline_code_theme="ansi_dark", code_theme="ansi_dark"), title=doc_id, border_style="yellow")
    # terminal width should always be greater then 40 but if it is then minus the width by 50
    if terminal_width > 70:
        console.print(md, width=100)
    else:
        console.print(md)
    