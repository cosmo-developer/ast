#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include EXP_H

int main(int argc, char **argv) {
	struct ast_node* node=new_ast();
	struct ast_node* num=CAST_NODE(new_num(FLOAT,0,100.22,0,0,0));
	
	return 0;
}
