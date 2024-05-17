/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:17:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/17 12:18:24 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>


#include <sys/stat.h>
#include <stdio.h>

int main() {
	char cwd[PATH_MAX];
    const char *path = "/Users/obrittne";
    struct stat path_stat;


    // Call stat() to get information about the path
    if (stat(path, &path_stat) == 0) {
        // Check if it is a directory
        if (S_ISDIR(path_stat.st_mode)) {
          if (chdir(path) == 0) {
                printf("Successfully changed current working directory to %s\n", path);
            } else {
                perror("chdir");
                printf("Failed to change current working directory to %s\n", path);
            }
        } else {
            printf("%s exists but is not a directory\n", path);
        }
    } else {
        perror("stat");
        printf("Could not retrieve information about %s\n", path);
    }
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd");
        return 1;
    }
    return 0;
}