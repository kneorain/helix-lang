#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>


std::unordered_set<std::string> BODY_REQUIRED_KEYWORDS = {
    "if", "else", "while", "for", "case", "default", "fn", "class",
    "struct", "interface", "enum", "union", "try", "catch", "finally", "throw", "thread"
};


// Helper function to split a string by a delimiter
std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start, end));
    return tokens;
}


// Helper function to join a vector of strings
std::string join(const std::vector<std::string> &tokens, const std::string &delimiter) {
    std::ostringstream imploded;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it != tokens.begin()) {
            imploded << delimiter;
        }
        imploded << *it;
    }
    return imploded.str();
}


// make a join function that takes a vector of any type and a delimiter  and takes in a string ref to modify
std::string* join(const std::vector<std::string> &tokens, const std::string &delimiter, std::string* result) {
    std::ostringstream imploded;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it != tokens.begin()) {
            imploded << delimiter;
        }
        imploded << *it;
    }
    *result = imploded.str();
    return result;
}

char* pre_process(char* lines) {
    std::string linesStr(lines);
    auto splitLines = split(lines, "|line_sep<:>line_sep|");

    std::vector<std::string> stack;
    std::vector<std::string> currentLine;
    std::vector<std::vector<std::string>> finalLines;
    bool firstInst = true;
    bool inForLoop = false;
    int indentLevel = 0;

    for (size_t index = 0; index < splitLines.size(); ++index) {
        std::string& token = splitLines[index];

        // Assuming BODY_REQUIRED_KEYWORDS is a predefined set of strings
        if (BODY_REQUIRED_KEYWORDS.find(token) != BODY_REQUIRED_KEYWORDS.end()) {
            stack.push_back(token);
            indentLevel++;
            firstInst = true;
        } else if (token == "{") {
            if (!firstInst) {
                indentLevel++;
            }
            if (stack.size() == static_cast<size_t>(indentLevel)) {
                splitLines[index] = ":";
                splitLines.insert(splitLines.begin() + index + 1, "<\\n>");
                firstInst = false;
            }
            if (splitLines[index + 2] == "}") {
                splitLines[index + 2] = "}";
                splitLines.insert(splitLines.begin() + index + 3, "<\\r>");
            }
        } else if (token == "}") {
            if (stack.size() == static_cast<size_t>(indentLevel)) {
                splitLines[index] = "<\\n>";
                indentLevel--;
                stack.pop_back();
            } else {
                indentLevel--;
            }
        }

        if (token == "<\\r>") {
            splitLines[index - 5] = "<\\r1>";
        }

        if (token == ";") {
            splitLines[index] = "<\\n>";
        }

        if (splitLines[index] == "<\\n>") {
            splitLines.insert(splitLines.begin() + index + 1, "<\\t:" + std::to_string(indentLevel) + ">");
        }

        if (token == "..." && splitLines[index + 1] != "<\\n>") {
            splitLines.insert(splitLines.begin() + index + 1, "<\\n>");
        }

        if (token == "<\\r>") {
            for (int i = index; i >= 0; --i) {
                if (splitLines[i] == "<\\r1>") {
                    break;
                } else {
                    splitLines[i] = "";
                }
            }
        }

        if (token == ";") {
            splitLines[index] = "<\\n>";
        }
    }
 
    for (size_t index = 0; index < splitLines.size(); ++index) {
        std::string& token = splitLines[index];
        if (token == "for") {
            inForLoop = true;
        }
        if (inForLoop) {
            if (token == "<\\n>") {
                splitLines[index] = ";";
                if (splitLines[index + 1].substr(0, 5) == "<\\t:") {
                    splitLines[index + 1] = "";
                }
            } else if (token == ":") {
                inForLoop = false;
            }
        }
    }

    // Remove empty strings
    splitLines.erase(std::remove(splitLines.begin(), splitLines.end(), ""), splitLines.end());
    
    for (size_t index = 0; index < splitLines.size(); ++index) {
        std::string& token = splitLines[index];
        if (token == "<\\n>") {
            finalLines.push_back(currentLine);
            currentLine.clear();
        } else {
            currentLine.push_back(token);
        }
    }

    if (!currentLine.empty()) {
        finalLines.push_back(currentLine);
    }

    for (size_t index = 0; index < finalLines.size(); ++index) {
        std::vector<std::string>& i = finalLines[index];
        if (i.size() == 1 && i[0].substr(0, 5) == "<\\t:") {
            finalLines[index].clear();
        }
    }

    std::string finalString = join(splitLines, "|line_sep<:>line_sep|");

    char* result = new char[finalString.length() + 1];
    strcpy(result, finalString.c_str());

    return result;
}

/*
convert this to a C function
def TOKENIZE(file: str) -> list[list[str]]:
    """
    \n Inputs: the code to split into tokens
    \n Outputs: the split code
    \n This function splits the code into a list of words and operators
    """
    tokenized_lines:    list[str] = []
    in_block_comment:   bool      = False

    for line in lines:
        stripped_line = line.strip()

        if stripped_line.startswith(BLOCK_COMMENT):
            in_block_comment = not in_block_comment
            continue

        if not in_block_comment and not stripped_line.startswith(COMMENT):
            tokenized_lines.extend(TOKENIZE_LINE(line))

    if in_block_comment:
        raise Exception("Unclosed block comment")
    
    return [token.split("|nested_line_sep<:>nested_line_sep|") for token in pre_process('|line_sep<:>line_sep|'.join(tokenized_lines)).split("|line_sep<:>line_sep|")]

*/

extern "C" {
    char* process(char* input) {
        return pre_process(input);
    }
}