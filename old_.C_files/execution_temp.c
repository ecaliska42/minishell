// static int	child_files(t_parse **comm) //WAS CALLED AT VERY FIRST LINE IN CHILD
// {
// 	int	trunc;
// 	int	append;

// 	trunc = O_WRONLY | O_CREAT | O_TRUNC;
// 	append = O_WRONLY | O_CREAT | O_APPEND;
// 	if ((*comm)->infile)
// 	{
// 		if ((*comm)->infile_type == INPUT)
// 			(*comm)->infd = open((*comm)->infile, O_RDONLY);
// 		else if ((*comm)->infile_type == HEREDOC)
// 			heredoc((*comm), (*comm)->infile);
// 		if ((*comm)->infile_type == INPUT && (*comm)->infd == -1)
// 			perror("INFD ERROR1:");
// 	}
// 	if ((*comm)->outfile)
// 	{
// 		if ((*comm)->outfile_type == OUTPUT)
// 			(*comm)->outfd = open((*comm)->outfile, trunc, 0644);
// 		else if ((*comm)->outfile_type == APPEND)
// 			(*comm)->outfd = open((*comm)->outfile, append, 0644);
// 		if ((*comm)->outfd == -1)
// 			perror("OUTFD ERROR1:");
// 	}
// 	return (SUCCESS);
// }

