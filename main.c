#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *stream = NULL;
int task_type = 0;
int doing_task = 0;
char task[256];
char cmd[512];
int len_task = 0;
int ret = 0;
int backup = 0;

void preprocess(char line[], int len) {
  switch (line[len - 1])
  {
    case '\n':
      line[--len] = '\0';
      break;
    default:
      break;
  }

  char *ptr = line;

  while (true)
  {
    switch (*ptr)
    {
      case ' ':
      case '\t':
        ptr++, len--;
        continue;
    }

    break;
  }

  while (true)
  {
    switch (ptr[len - 1])
    {
      case ' ':
      case '\t':
        ptr[--len] = '\0';
        continue;
    }

    break;
  }

  memcpy(line, ptr, len + 1);
  return;
}

void parse(char *ptr, int len) {
  switch (*ptr)
  {
    case '\0':
    case '#':
      return;
    case ':':
      switch (doing_task)
      {
        case 0:
          fputs(ptr, stderr);
          fputs(" >> not inside task\n", stderr);
          fclose(stream);
          exit(EXIT_FAILURE);
        case 1:
          break;
      }

      switch (task_type)
      {
        case 0:
        case 1:
        case 2:
          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          
          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          ret = system(cmd);
          break;
        case 3:
          switch (ret)
          {
            case 0:
              break;
            default:
              return;
          }

          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          
          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              puts(" >> command too long\n");
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          ret = system(cmd);
          break;
        case 4:
          switch (ret)
          {
            case 0:
              return;
            default:
              break;
          }

          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          
          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          ret = system(cmd);
          break;
        case 5:
          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          strncat(cmd, " > /dev/null", 13);

          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          ret = system(cmd);
          break;
      }

      switch (task_type)
      {
        case 0:
        case 5:
          break;
        case 1:
          switch (ret)
          {
            case 0:
              break;
            case 1:
              fputs(cmd, stderr);
              fputs(" >> execution failed\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            case 127:
              fputs(cmd, stderr);
              fputs(" >> command not found\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            case 130:
              fputs(cmd, stderr);
              fputs(" >> interrupted\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            case 139:
              fputs(cmd, stderr);
              fputs(" >> invalid memory access\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            case 32512:
              fputs(cmd, stderr);
              fputs(" >> force quit\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            default:
              fputs(cmd, stderr);
              fputs(" >> other error\n", stderr);
              fclose(stream);
              exit(ret);
              break;
          }

          break;
        case 2:
          switch (ret)
          {
            case 0:
              break;
            case 1:
              fputs(cmd, stderr);
              fputs(" >> execution failed\n", stderr);
              break;
            case 127:
              fputs(cmd, stderr);
              fputs(" >> command not found\n", stderr);
              break;
            case 130:
              fputs(cmd, stderr);
              fputs(" >> interrupted\n", stderr);
              break;
            case 139:
              fputs(cmd, stderr);
              fputs(" >> invalid memory access\n", stderr);
              break;
            case 32512:
              fputs(cmd, stderr);
              fputs(" >> force quit\n", stderr);
              fclose(stream);
              exit(ret);
              break;
            default:
              fputs(cmd, stderr);
              fputs(" >> other error\n", stderr);
              break;
          }

          break;
      }

      break;
    case '@':
      task_type = 0;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    case '!':
      task_type = 1;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    case '-':
      switch (doing_task)
      {
        case 0:
          fputs(ptr, stderr);
          fputs(" >> not inside task\n", stderr);
          fclose(stream);
          exit(EXIT_FAILURE);
        case 1:
          break;
      }

      switch (task_type)
      {
        case 0:
        case 1:
        case 2:
          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          
          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          backup = ret;
          ret = system(cmd);
          break;
        case 3:
          switch (ret)
          {
            case 0:
              break;
            default:
              return;
          }

          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          
          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          backup = ret;
          ret = system(cmd);
          break;
        case 4:
          switch (ret)
          {
            case 0:
              return;
            default:
              break;
          }

          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);

          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          backup = ret;
          ret = system(cmd);
          break;
        case 5:
          memcpy(cmd, task, len_task + 1);
          strncat(cmd, " ", 2);
          strncat(cmd, ++ptr, len);
          strncat(cmd, " > /dev/null", 13);

          switch (strlen(cmd))
          {
            case sizeof(cmd):
              fputs(ptr, stderr);
              fputs(" >> command too long\n", stderr);
              fclose(stream);
              exit(EXIT_FAILURE);
              break;
            default:
              break;
          }

          backup = ret;
          ret = system(cmd);
          break;
      }

      switch (ret)
      {
        case 32512:
          fputs(cmd, stderr);
          fputs(" >> force quit\n", stderr);
          fclose(stream);
          exit(ret);
          break;
        default:
          break;
      }

      ret = backup;
      break;
    case '$':
      task_type = 2;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    case '/':
      task_type = 3;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    case '^':
      task_type = 4;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    case '%':
      task_type = 5;
      doing_task = 1;
      memcpy(task, ++ptr, len);
      len_task = strlen(task);
      break;
    default:
      fputs(ptr, stderr);
      fputs(" >> unknown command\n", stderr);
      fclose(stream);
      exit(EXIT_FAILURE);
      return;
  }

  return;
}

int main(int argc, char **argv) {
  char line[256];
  
  while (*++argv)
  {
    stream = fopen(*argv, "rb");

    if (!stream)
    {
      fputs(*argv, stderr);
      fputs(" >> file not found\n", stderr);
      return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), stream))
    {
      int len = strlen(line);
      preprocess(line, len);
      parse(line, len);
    }

    fclose(stream);
    continue;
  }
  return EXIT_SUCCESS;
}
