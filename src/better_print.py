UNIT_OR_SINGLE_TESTING: bool | str = True # 'unit' or 'single' or False
from types import MappingProxyType as _MappingProxyType
from os import get_terminal_size
from typing import TextIO
from sys import stdout

_make_fg_color = lambda *color_triplet: '\x1b[38;2;{};{};{}m'.format(*color_triplet)
_make_bg_color = lambda *color_triplet: '\x1b[48;2;{};{};{}m'.format(*color_triplet)

COLORS = _MappingProxyType({
    'black'         : _make_fg_color(0, 0, 0),
    'white'         : _make_fg_color(255, 255, 255),
    'red'           : _make_fg_color(200, 0, 0),
    'green'         : _make_fg_color(0, 200, 0),
    'blue'          : _make_fg_color(0, 0, 200),
    'yellow'        : _make_fg_color(200, 200, 0),
    'cyan'          : _make_fg_color(0, 200, 200),
    'magenta'       : _make_fg_color(200, 0, 200),
    'gray'          : _make_fg_color(128, 128, 128),
    'bright black'  : _make_fg_color(128, 128, 128),
    'bright red'    : _make_fg_color(255, 0, 0),
    'bright green'  : _make_fg_color(0, 255, 0),
    'bright blue'   : _make_fg_color(0, 0, 255),
    'bright yellow' : _make_fg_color(255, 255, 0),
    'bright cyan'   : _make_fg_color(0, 255, 255),
    'bright magenta': _make_fg_color(255, 0, 255),
    'bright gray'   : _make_fg_color(128, 128, 128),
    "light red"     : _make_fg_color(255, 154, 153),
    "light green"   : _make_fg_color(153, 255, 153),
    "light blue"    : _make_fg_color(153, 153, 255),
    "light yellow"  : _make_fg_color(255, 255, 153),
    "light cyan"    : _make_fg_color(153, 255, 255),
    "light magenta" : _make_fg_color(255, 153, 255),
    "light gray"    : _make_fg_color(192, 192, 192),
    "text"          : _make_fg_color(233, 232, 232),
    "background"    : _make_fg_color(3, 2, 3),
    "primary"       : _make_fg_color(141, 17, 172),
    "secondary"     : _make_fg_color(16, 15, 15),
    "accent"        : _make_fg_color(224, 36, 74),
})
BG_COLORS = _MappingProxyType({
    'black'         : _make_bg_color(0, 0, 0),
    'white'         : _make_bg_color(255, 255, 255),
    'red'           : _make_bg_color(255, 0, 0),
    'green'         : _make_bg_color(0, 255, 0),
    'blue'          : _make_bg_color(0, 0, 255),
    'yellow'        : _make_bg_color(255, 255, 0),
    'cyan'          : _make_bg_color(0, 255, 255),
    'magenta'       : _make_bg_color(255, 0, 255),
    'gray'          : _make_bg_color(128, 128, 128),
    'bright black'  : _make_bg_color(128, 128, 128),
    'bright red'    : _make_bg_color(255, 0, 0),
    'bright green'  : _make_bg_color(0, 255, 0),
    'bright blue'   : _make_bg_color(0, 0, 255),
    'bright yellow' : _make_bg_color(255, 255, 0),
    'bright cyan'   : _make_bg_color(0, 255, 255),
    'bright magenta': _make_bg_color(255, 0, 255),
    'bright gray'   : _make_bg_color(128, 128, 128),
    "text"          : _make_fg_color(233, 232, 232),
    "background"    : _make_fg_color(3, 2, 3),
    "primary"       : _make_fg_color(141, 17, 172),
    "secondary"     : _make_fg_color(16, 15, 15),
    "accent"        : _make_fg_color(224, 36, 74),
    'default'       : '\x1b[49m',
})
STYLES = _MappingProxyType({
    'bold': '\x1b[1m',
    'dim': '\x1b[2m',
    'italic': '\x1b[3m',
    'underline': '\x1b[4m',
    'blink': '\x1b[5m',
    'reverse': '\x1b[7m',
    'hidden': '\x1b[8m',
    'strike': '\x1b[9m',
})
WHITESPACE_ESCAPE = _MappingProxyType({
    '\n' : '\\n',
    '\t' : '\\t',
    '\r' : '\\r',
    '\b' : '\\b',
    '\f' : '\\f',
    '\v' : '\\v',
})
BORDER_TYPES = _MappingProxyType({
    1  : r'╭ ─ ╮ │ ╰ ╯',
    2  : r'┌ ─ ┐ │ └ ┘',
    3  : r'┏ ━ ┓ ┃ ┗ ┛',
    4  : r'╔ ═ ╗ ║ ╚ ╝',
    5  : r'╒ ═ ╕ │ ╘ ╛',
    6  : r'╓ ─ ╖ ║ ╙ ╜',
    7  : r'+ - + | + +',
    8  : r'. - . | . .',
    9  : r'* - * | * *',
    10 : r'# - # | # #', 
    11 : r'= - = | = =',
    12 : r'~ - ~ | ~ ~',
    13 : r'_ - _ | _ _',
    14 : r'^ - ^ | ^ ^',
    15 : r'` - ` | ` `',
    16 : r'/ - \ | \ /',
    17 : r'< - > | \ /',
    18 : r'( - ) | ) (',
    19 : r'[ - ] | ] [',
    20 : r'{ - } | } {',
})

def isdigit(l: list) -> bool:
    """Checks if all the elements in a list are digits

    Args:
        l (list): the list to check

    Returns:
        bool: True if all the elements are digits, False otherwise
    """
    for i in l:
        if not i.strip().isdigit(): return False
    return True
def _process_bg_color(bg: str) -> str:
    """Processes the background color and returns the unicode escape sequence
    Args:
        bg (str): the background color
    Returns:
        str: the background color as a unicode escape sequence
    """
    bg_list: list[str] = []
    
    if not bg.startswith('rgb('):
        try: bg = BG_COLORS[bg.lower().strip()]
        except KeyError: raise ValueError('Invalid color ' + str(bg).strip())
    else:
        bg_list = bg_list.split('rgb')[1].split('(')[1].split(')')[0].split(',')
        if len(bg_list) != 3 or not isdigit(bg_list) or any([int(i.strip()) > 255 for i in bg_list]): 
            raise ValueError('Invalid rgb color ' + str(bg_list))
        for index, i in enumerate(bg_list): bg_list[index] = int(i.strip())
        bg = _make_bg_color(bg_list[0], bg_list[1], bg_list[2])
    return bg
def _process_style(color: list[str]) -> str:
    """Processes the color and style and returns the unicode escape sequence
    Args:
        color (list[str]): a list of strings containing the color and style or just the color or just the style
    Returns:
        str: the style and color as unicode escape sequences
    """

    color = [color[0], ' '.join(color[1:])]
    style: str = ''

    if color[0].lower() in STYLES:
        style = STYLES[color[0].lower().strip()]
        if not color[1].startswith('rgb('):
            try: color = COLORS[color[1].lower().strip()] if color[1].lower().strip() != '' else ''
            except KeyError: raise ValueError('Invalid color ' + str(color[1]).strip())
        else:
            color = color[1].split('rgb')[1].split('(')[1].split(')')[0].split(',')
            if len(color) != 3 or not isdigit(color) or any([int(i.strip()) > 255 for i in color]): 
                raise ValueError('Invalid rgb color ' + str(color))
            for index, i in enumerate(color): color[index] = int(i.strip())
            color = _make_fg_color(color[0], color[1], color[2])
    else:
        color = ' '.join([color[0].lower(), color[1].lower()]).strip()
        if not color.startswith('rgb('):
            try: color = COLORS[color.strip()]
            except KeyError: raise ValueError('Invalid color ' + str(color).strip())
        else:
            color = color.split('rgb')[1].split('(')[1].split(')')[0].split(',')
            if len(color) != 3 or not isdigit(color) or any([int(i.strip()) > 255 for i in color]): 
                raise ValueError('Invalid rgb color ' + str(color))
            for index, i in enumerate(color): color[index] = int(i.strip())
            color = _make_fg_color(color[0], color[1], color[2])
    return style + color
def _process_justify(justify: str,
                     width: int,
                     word_wrap: bool,
                     objects: list[str],
                     terminal_width: int) -> str:
    """Processes the justification and returns the justified string

    Args:
        justify (str): the justification method (left, right, center)
        width (int): the max width to justify to
        word_wrap (bool): whether or not to word_wrap the text using words or characters
        objects (list[str]): the objects to justify
        terminal_width (int): the width of the terminal
    Returns:
        str: the justified string
    """
    
    terminal_width = terminal_width + 1
    width = width + 1 if width else width
    
    if not width and not word_wrap:
        objects = objects.split('\n')
        for index, i in enumerate(objects):
            objects[index] = objects[index].center(terminal_width) if justify == 'center' else \
            objects[index].ljust(terminal_width) if justify == 'left' else objects[index].rjust(terminal_width) \
            if justify == 'right' else objects[index]
        objects = '\n'.join(objects)
        return objects

    for index, i in enumerate(objects):
        objects[index] = i.split('\n')
        for index2, i2 in enumerate(objects[index]):
            objects[index][index2] = objects[index][index2].center(width) if justify == 'center' else \
            objects[index][index2].ljust(width) if justify == 'left' else objects[index][index2].rjust(width) \
            if justify == 'right' else objects[index][index2]
        objects[index] = '\n'.join(objects[index])
        
    objects = '\n'.join(objects)
    return objects
def _process_width(width: int,
                   word_wrap: bool,
                   objects: list[str],
                   justify: str) -> str:
    """Processes the width and returns the justified string

    Args:
        width (int): the max width to justify to
        word_wrap (bool): whether or not to word_wrap the text using words or characters
        objects (list[str]): the objects to justify
        justify (str): the justification method (left, right, center)
    Returns:
        str: the justified string
    """
    new_objects: list = []
    length_count: int = 0
    temp_list: list = []
    if not word_wrap:
        objects = [objects[:width].strip(), objects[width:].strip()]
        while len(objects[-1].strip()) >= width:
            objects.insert(-1, objects[-1][:width].strip())
            objects[-1] = objects[-1][width:].strip()
        return objects
    else:
        objects = objects.split(' ')
        len_i: int = 0
        for i in objects:
            len_i = len(i)
            if len_i + length_count >= width:
                new_objects.append(' '.join(temp_list))
                temp_list, length_count = [], 0
            temp_list.append(i)
            length_count += len_i + 1
        else:
            new_objects.append(' '.join(temp_list))
            
        if not justify: return '\n'.join(new_objects)
        return new_objects
def _process_border(border_type: bool,
                    objects: str,
                    terminal_width: int,
                    width: int) -> str:
    """Processes the border and returns the justified string

    Args:
        border_type (bool): The type of border to use (1 - 20)
        objects (str): Objects to border
        terminal_width (int): The width of the terminal
        width (int): The width of the border

    Returns:
        str: The bordered objects
    """
    
    if not width:
        width = terminal_width
    
    new_objects: list = []
    top_left, horizontal, top_right, vertical, bottom_left, bottom_right = BORDER_TYPES.get(border_type).split(' ')
    
    for i in objects.split('\n'):
        new_objects.append(vertical + i + (' ' * (width - len(i) + 1)) + vertical)
    
    return ((top_left + (horizontal * (width + 1)) + top_right) + '\n') + \
             '\n'.join(new_objects) + '\n' + ((bottom_left + (horizontal * (width + 1)) + bottom_right))
def _arg_check( objects: list[str],
                sep: str,
                end: str,
                flush: bool,
                style: str,
                justify: str,
                width: int,
                bg: str,
                file: TextIO,
                word_wrap: bool,
                border_type: bool,
                return_objects: bool,
                surround_lines: bool,
                border: int) -> None:
    """Checks the arguments for errors"""
    if sep:
        if not isinstance(sep, str): raise TypeError('sep must be a string')
    if end:
        if not isinstance(end, str): raise TypeError('end must be a string')
    if flush:
        if not isinstance(flush, bool): raise TypeError('flush must be a boolean')
    if style or justify or width or bg or file:
        if not isinstance(style, str) and style is not None: raise TypeError('style must be a string')
        if not isinstance(justify, str) and justify is not None: raise TypeError('justify must be a string')
        if not isinstance(width, int) and width is not None: raise TypeError('width must be an integer')
        if not isinstance(bg, str) and bg is not None: raise TypeError('bg must be a string')
        if not isinstance(file, TextIO) and file is not None: raise TypeError('file must be a file object')
    if word_wrap:
        if not isinstance(word_wrap, bool): raise TypeError('word_wrap must be a boolean')
    if return_objects:
        if not isinstance(return_objects, int): raise TypeError('return_objects must be an integer')
        if return_objects not in [0, 1, 2]: raise ValueError('return_objects must be 0, 1, or 2')
    if surround_lines:
        if not isinstance(surround_lines, int): raise TypeError('surround_lines must be an integer')
        if surround_lines < -1: raise ValueError('surround_lines must be greater than or equal to -1')
    if border:
        if not isinstance(border, bool): raise TypeError('border must be a boolean')
    if border_type:
        if not isinstance(border_type, int): raise TypeError('border_type must be an integer')
        if border_type not in range(1, 21): raise ValueError('border_type must be between 1 and 20')
def color_print(*objects,
                sep: str = '',
                end: str = '\n',
                flush: bool = False,
                style: str | None = None, # type: ignore
                justify: str | None = None,
                width: int | None = None,
                word_wrap: bool = False,
                bg: str | None = None,
                file: TextIO | None = None,
                return_objects: int = False,
                surround_lines: int = 0,
                border: bool = False,
                border_type: int = 0,
                no_arg_check: bool = True,
                **kwargs) -> list[str] | None:

    """Prints colored text to the terminal.

    Args:
        *objects: Any number of arguments to be printed.
        sep: The separator between printed arguments. default: `''`
        end: The end character to be printed. default: `'\n'`
        flush: Whether to flush the output buffer. default: `False`
        style: The style of the text to be printed. default: `None`
        justify: The justification of the text to be printed. default: `left`
        width: The width of the text to be printed in characters. default: `None`
        word_wrap: Whether to word_wrap. If True, the text will be wrapped at the end of a word if it exceeds the width. 
            If False, the text will be wrapped at the end of a character if it exceeds the width. default: `True`
        bg: The background color of the text to be printed. default: `None`
        file: The file to be printed to. default: `None`
        return_objects: Whether to return the objects instead of printing them or after printing them or none 
                        (0: no return, 1: return after printing, 2: return before printing). default: `0`
        surround_lines: How many lines to surround the text with blank lines. (-1: to the height of the terminal,
            0: none, any other number) default: `0`
        border: Whether to surround the text with a border. default: `False`
        border_type: The type of border to surround the text with (1 - 20). default: `1` 
        no_arg_check: Whether to check the arguments for errors. default: `True`
    Returns:
        None or list[str]: The objects printed or to be printed.
    """
    if not no_arg_check: _arg_check(objects, sep, end, flush, style, justify, width, bg, file,
                                    word_wrap, border_type, return_objects, surround_lines, border)
    if not border_type and border:
        border_type = 1
    if border_type:
        border = True
    
    get_terminal_size_obj = get_terminal_size()
    
    terminal_width, terminal_height = get_terminal_size_obj.columns - 1 if not border \
        else get_terminal_size_obj.columns - 3, get_terminal_size_obj.lines - 1

    style: list[str] = style.split(' ') if style else None # type: ignore

    objects = list(objects)
    for index, i in enumerate(objects):
        if not isinstance(i, str):
            i = str(i)
        objects[index] = i
    objects_list, objects = objects.copy(), sep.join(objects)

    if justify == 'justify': justify = 'left'; word_wrap = False
    if style: style = _process_style(style)
    if bg: bg = _process_bg_color(bg)
    if word_wrap and not width: width = terminal_width
    if width: objects = _process_width(width, word_wrap, objects, justify)
    if justify: objects = _process_justify(justify, width, word_wrap, objects, terminal_width)
    
    if surround_lines == -1: 
        surround_lines = (terminal_height - (len(objects.split('\n')) - 1)) / 2
        surround_lines = int(surround_lines) * -1 if surround_lines < 0 else int(surround_lines)
    if surround_lines:
        objects = (((' ' * (terminal_width + 1 if not width else width + 1)) + '\n') * surround_lines
                    ) + (objects + '\n' if not objects.endswith('\n') else ''
                    ) + (((' ' * (terminal_width + 1 if not width else width + 1)) + '\n') * surround_lines)
        objects = objects[:-2]
    
    if border: objects = _process_border(border_type, objects, terminal_width, width)
    
    if style: objects = style + objects
    if bg: objects = bg + objects
    
    if return_objects == 1: return objects_list
    testing = False
    
    try:
        testing = kwargs['test']
    except KeyError:
        if kwargs: raise TypeError(f'color_print() got an unexpected keyword argument "{list(kwargs.keys())[0]}"')
        
    if file:
        file.write(objects + "\033[0m" + end)
        if flush: file.flush()
    else:
        stdout.write(objects + "\033[0m" + end) if not testing else None
        if flush: stdout.flush()

    return objects_list if return_objects == 2 else None

if __name__ == '__main__':
    """
    Run a test of the color_print function.
    """
    attempts = 1000 if UNIT_OR_SINGLE_TESTING == 'unit' else 1 if UNIT_OR_SINGLE_TESTING == 'single' else 0
    if UNIT_OR_SINGLE_TESTING:
        color_print(f'Running {attempts} tests', justify='center', border=True, style="rgb(140, 30, 200)", surround_lines=2)
        from cProfile import Profile
        from pstats import Stats
        from time import time
        profile = Profile()
        start = time()
        profile.enable()
        for i in range(attempts):
            color_print('hello world', word_wrap=False)
        profile.disable()
        color_print(f"Total time taken: {time() - start}", justify='center', border=True, style="rgb(140, 255, 200)")
        Stats(profile).sort_stats('tottime').print_stats(10)
    else:
        color_print(f'"{__file__}"\n\ntesting disabled, check the UNIT_OR_SINGLE_TESTING variable.', justify='center', 
                    border=True, style="bright red", surround_lines=1)
    exit()
    
# 0.0044138431549072266 regular print
# 0.003928184509277344 color_print
# 11 % faster than regular print (0.0004856586456298828 seconds faster)* based on this testing for 1000 attempts