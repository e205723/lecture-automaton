#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  regex_t preg;
  int result, i, match_count;
  regmatch_t *pmatch;
  char *target = "Brouhaha!";
  int target_len = strlen(target);
  int offset = 0;

  // Compile the regular expression pattern
  result = regcomp(&preg, "(h|a)aha*", REG_EXTENDED);
  if (result != 0) {
    printf("fail to compile regex\n");
    return 1;
  }

  // Perform the pattern matching
  pmatch = malloc(sizeof(regmatch_t));
  result = regexec(&preg, target + offset, 1, pmatch, 0);
  match_count = 0;
  while (result == 0 && offset < target_len) {
    printf("pattern match succeeded\n");
    printf("Match: %.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so), target + offset + pmatch[0].rm_so);
    match_count++;
    offset += pmatch[0].rm_eo;
    pmatch = realloc(pmatch, (match_count + 1) * sizeof(regmatch_t));
    result = regexec(&preg, target + offset, 1, &pmatch[match_count], REG_NOTBOL);
  }
  if (result != REG_NOMATCH) {
    printf("fail to execute regrex\n");
    return 1;
  }
  free(pmatch);

  regfree(&preg);

  return 0;
}

