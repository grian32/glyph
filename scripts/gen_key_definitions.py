# generates key definitions for GLYPH based on the GLFW ones in glfw3.h
import re

if __name__ == "__main__":
    file = open("/usr/include/GLFW/glfw3.h", "r")

    content = file.read()
    match = re.findall(r"#define GLFW_KEY_\w+\s+(?:-|)\d+", content)
    for x in match:
        print(str(x).replace("GLFW", "GLYPH").replace("-1", "(-1)"))
    print()
    match = re.findall(r"#define GLFW_MOUSE_\w+\s+(?:-|)(?:\w+|\d+)", content)
    for x in match:
        print(str(x).replace("GLFW", "GLYPH"));