CODES: dict[str, str] = {
    "1": "_g_1_",
    "2": "_d_2_",
    "3": "_J_3_",
    "4": "_a_4_",
    "5": "_V_5_",
    "6": "_v_6_",
    "7": "_D_7_",
    "8": "_u_8_",
    "9": "_Y_9_",
}

def unicode_to_str(s: str) -> str:
    val: str = str(ord(s))
    out: str = ""
    for i in val:
        out += CODES[i]
    return out

def reverse_unicode(s: str) -> str:
    reversed_codes: dict[str, str] = {v: k for k, v in CODES.items()}
    val: str = ""
    
    def something(code):
        nonlocal val, s
        if s.startswith(code):
            val += reversed_codes[code]
            s = s[len(code):]

    def iterwe():
        nonlocal s
        yield True if s else False
    
    while s:
        [something(code) for code in reversed_codes]

    return chr(int(val))

# Testing with the emoji "😭"
encoded = unicode_to_str("😭")
print("Encoded:", encoded)
decoded = reverse_unicode(encoded)
print("Decoded:", decoded)