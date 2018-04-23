void print(char *s)
{
write(1, s, strlen(s));
}

int main()
{
char *addr;

addr = malloc(16);
free((void*)0);
free((void *)addr + 5);
if (realloc((void *)addr + 5, 10) == (void*)0)
print("Bonjour\n");
}
