#########################################################################
# File Name: cmd.sh
# Author: Harvey
# mail: hanwei@zhihuihutong.com
# Created Time: 2018年03月21日 星期三 17时13分32秒
#########################################################################
#!/bin/bash

valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./a.out 123
