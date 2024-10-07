#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("What name should the project have? ");
    char project_name[100];
    scanf("%s", project_name);

    char project_dir[100];
    sprintf(project_dir, "%s", project_name);

    if (mkdir(project_dir, 0755) == -1) {
        perror("mkdir");
        return 1;
    }

    char cmakelists_file[100];
    sprintf(cmakelists_file, "%s/CMakeLists.txt", project_dir);
    FILE *cmake_file = fopen(cmakelists_file, "w");
    if (cmake_file == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(cmake_file, "cmake_minimum_required(VERSION 3.10)\nproject(%s)\nadd_executable(main main.c)\n", project_name);
    fclose(cmake_file);

    char src_dir[100];
    sprintf(src_dir, "%s/src", project_dir);
    if (mkdir(src_dir, 0755) == -1) {
        perror("mkdir");
        return 1;
    }

    char main_cpp_file[100];
    sprintf(main_cpp_file, "%s/main.c", src_dir);
    FILE *f = fopen(main_cpp_file, "w");
    if (f == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "#include <stdio.h>\n\nint main() {\n    printf(\"Hello, %s!\\n\", project_name);\n    return 0;\n}", project_name);
    fclose(f);

    return 0;
}