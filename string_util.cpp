#include <dirent.h>
#include <regex>
#include <vector>
#include "string_util.h"

using namespace std;

/** https://thispointer.com/c-how-to-get-filename-from-a-path-with-or-without-extension-boost-c17-filesytem-library/ */
std::string getFileName(std::string filePath) {

    // Get last position of "/" char
    std::size_t sepPos = filePath.rfind("/");

    // If the file sepearatoor is found, extract the last part of the string that corresponds
    // to the file name
    if (sepPos != std::string::npos) {
        int n = filePath.size() - (sepPos + 1);
        return filePath.substr(sepPos + 1, n);
    }

    // If the "/" sep. is  not found, assumes filename=path
    return filePath;
}

/** \brief Get the directory name.
 */
std::string getDirName(std::string filePath) {

    // Get last position of "/" char
    std::size_t sepPos = filePath.rfind("/");

    // If "/" is found, assumes extracts the part that corresponds to the dirname
    if (sepPos != std::string::npos) {
        return filePath.substr(0, sepPos + 1);
    }

    // if "/" not found, assumes that file=path, hence no directory
    return "";
}


/**  \brief Extract the list of files that match a given pattern.
 *
 * @param file_prefix File prefix
 *
 * @author Nicolas Barrier
 *
*/
std::vector<std::string> get_files(const string file_prefix) {

    std::string path = getDirName(file_prefix);
    std::string name = getFileName(file_prefix);

    // If path is null, forces it to be "./"
    if (path == "") {
        path = "./";
    }

    // Compile the regular expression from the prefix name
    std::regex regexp_file(name.c_str());

    // init output list of strings
    std::vector<std::string> output;

    DIR *dp;
    struct dirent *dirp;
    int cpt = 0;

    dp = opendir(path.c_str());

    // Check if folder can be opened
    if (dp == NULL) {
        printf("Opendir function fails %s", path.c_str());
        exit(1);
    }

    // Loop over the elements contained in the parent forcing folder
    while ((dirp = readdir(dp)) != NULL) {

        // If the name of the current file does not match file pattern, skip
        if (!regex_match(dirp->d_name, regexp_file)) {
            continue;
        }

        // Iterates the number of matches
        cpt += 1;

        // Reconstructs path name
        std::stringstream ss;
        ss.str("");
        ss << path << std::string(dirp->d_name);

        // add path name into list
        output.push_back(ss.str());
    }

    closedir(dp);

    if (cpt == 0) {
        printf("No files found matching %s %s\n", path.c_str(), name.c_str());
        exit(1);
    }

    // alphabetical order
    sort(output.begin(), output.end());

    return output;
}
