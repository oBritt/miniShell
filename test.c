/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:17:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 19:53:44 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int main() {
    const char *new_path = "";
    DIR *dir = opendir(new_path);

    // Check if the directory can be opened
    if (dir == NULL) {
        if (errno == ENOENT) {
            fprintf(stderr, "Error: %s does not exist\n", new_path);
        } else if (errno == ENOTDIR) {
            fprintf(stderr, "Error: %s is not a directory\n", new_path);
        } else {
            perror("opendir() error");
        }
        return 1;
    }

    // Close the directory as it exists and is a directory
 	 closedir(dir);

    // Change the current working directory
    if (chdir("/etc/passwd") != 0) {
        perror("chdir() error");
        return 1;
    }

    // Print the new working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    return 0;
}