# Utility
## Overview
This project I created because I mistakenly run a command.
```bash
sudo rm -rf ~
```

Problem Begins.
- I lost all my personal data. Hope fully I had a backup of the data but it is outdated.
- I lost my personal customization which I had acquired from reading and watching may tutorial and articles.

Solution:
- I had recovered the lost data by the tool named [`photorec`](https://www.cgsecurity.org/testdisk_doc/)
- `photorec` recovered my data but my file name ware gone. It is default to identify the data. which file contain what.

**So I come up with this project to search all the xml file which contain some text and copy those file to different folder.**
### So I did it!

At this point of time. The tool name `grep` do not come across my mind. That I could use it. The best tool for doing things like this.
By googling and using AI I got this.
```bash
grep -rl --include="*.xml" "xfce4-panel" /path/to/source | xargs -I {} cp {} /path/to/destination
```

But, I did some coding to achieve this task. Feel free to have a look and I hope it will helpful to you. **Please give some comment and advice on the matter**

## Make your self
### Dependency
- [Conan](https://conan.io/)
- [CMake](https://cmake.org/)
- [RapidXML](https://github.com/Fe-Bell/RapidXML.git)
- [CLI11](https://github.com/CLIUtils/CLI11.git)
- [fmt](https://github.com/fmtlib/fmt.git)

```bash
git clone 
cd Utility
conan install --build=missing -s build_type=release
cmake -G "Ninja" -S . -B ./build/release -DCMAKE_BUILD_TYPE=release --preset conan-release
```

