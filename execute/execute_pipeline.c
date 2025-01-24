// #include "minishell.h"

// void set_fds(t_context, context, t_pipe *node)
// {
//     int pipe_fds[2];

    
// }
// void execute_pipeline(t_context context, t_ast_node *node)
// {
//     t_pipe *pipe;

//     pipe = node->node;
//     if (pipe->in_fd == -2)
//         pipe->in_fd = STDIN_FILENO;
//     if (pipe->out_fd == -2)
//         pipe->out_fd = STDOUT_FILENO;
// 	set_fds(context, pipe);

// }