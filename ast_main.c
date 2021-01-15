#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include EXP_H

int main(int argc, char **argv) {
	//evaluating (60+50)/2
	_node lnum=CAST_NODE(new_num(DOUBLE,0,0,50,0,0));
	_node rnum=CAST_NODE(new_num(DOUBLE,0,0,60,0,0));
	_node bin=CAST_NODE(new_bin_op(lnum,ADD,rnum));
	_node div=CAST_NODE(new_bin_op(bin,DIV,CAST_NODE(new_num(DOUBLE,0,0,2,0,0))));
	_value result=visit(div);
	printf("%lf\n",result->value.dval);
	free(result);
	CLEAN(bin);
	return 0;
}
