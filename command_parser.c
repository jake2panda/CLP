#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void help_me() {
	fprintf(stderr, "  	 !!!!!    Command line parser !!!!!\n");
	printf("														\n");
	printf("                       HELP LINE                     	\n");
	printf("                       _________                       \n");
	printf("													   	\n");
	printf("-h or --help			help menu\n");
	printf("-p or --port			port number\n");
	printf("-e or --myd			provide user info\n");
	exit(2);
}


int check_first_digit(char *val) {
	if (val[0] >= 48 && val[0] <= 57) {
		return 1;
	} else {
		return 0;
	}
}


int every_digit_checker(char *val) {
	for (int i = 0; i < strlen(val); i++) {
		if (val[i] <= 97 || val[i] >= 122) {
			return 0;
		}
	}
	return 1;
}


/* |  0 | 1 | 2 | 3 | 4 |
   a.out -e "eval" -p "pval"
*/

int main(int argc, char **argv) {
	// parse user cli

	/*
	User declared variables
	*/
	int arg_tracker = 1;

	if (argc == 1) {
		fprintf(stderr, "[!!] Usage <program_name> options. type -h or --help for help\n");
	}

	while (arg_tracker < argc && *argv[arg_tracker] == '-') {
		char *arg = "";
		char *longopt = "";
		arg = argv[arg_tracker] + 1;
		if (arg[0] == '-') {
			longopt = arg + 1;
			if (check_first_digit(longopt)) {
				fprintf(stderr, "[!!!] digit error\n");
				exit(-2);
			}
			/*
				here rigorous checker
			*/

			if (!every_digit_checker(longopt)) {
				fprintf(stderr, "[!!!] Invalid chatacter detected.. check your syntax\n");
				exit(-2);
			}
			if (strncmp(longopt, "help", 4) == 0) {
				help_me();
			} else if (strncmp(longopt, "port", 4) == 0) {
				arg_tracker += 1;
				int user_port = atoi(argv[arg_tracker]);
				fprintf(stderr, "[+] user port : %d\n", user_port);
				arg_tracker += 1;
			} else if (strncmp(longopt, "myd", 3) == 0) {
				arg_tracker += 1;
				char *user_eval = argv[arg_tracker];
				fprintf(stderr, "[+] user expr : %s\n", user_eval);
				arg_tracker += 1;
			} else {
				fprintf(stderr, "[!] Invalid options\n");
				arg_tracker++;
			}
		} else if (arg[0] == 'e') {
			char *eval = "";
			arg_tracker += 1; // arg_tracker = 2 --> eval
			arg = argv[arg_tracker];
			if (arg[0] != '-') {
				eval = arg;
				arg_tracker +=1; // now arg_tracker = 3 pointing to -p
			}
			printf("[+] e->>val : %s\n", eval);
		} else if (arg[0] == 'p') {	
			char *pval;
			arg_tracker += 1; // arg_tracker = 4 pointing pval
			arg = argv[arg_tracker];
			if (arg[0] != '-') {
				pval = arg;
				arg_tracker += 1; // arg_tracker = 5
			}
			printf("[+] p-->val : %s\n", pval);
		} else if (arg[0] == 'h') {
			help_me();
		}
		else {
			printf("[!!] out of options\n");
			arg_tracker++;
		}

	}

}
