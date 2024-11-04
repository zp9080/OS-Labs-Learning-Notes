
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS* p;
	int	 greatest_ticks = 0;
	int i;
	while (!greatest_ticks) {
		//先找高优先级分配处理器,找到了就结束循环
		int temp=highI;
		for(i=0;i<temp;i++){
			if(highP[i]!=-1 && proc_table[highP[i]].ticks>0){
				greatest_ticks=proc_table[highP[i]].ticks;
				p_proc_ready=&proc_table[highP[i]];
				break;
			}else if(highP[i]!=-1 && proc_table[highP[i]].ticks<=0){//时间片用完的进入中优先级，并分配MID_TICK，然后等待
				proc_table[highP[i]].ticks=MID_TICK;
				midP[midI++]=highP[i];

				int j;
				for(j=i;j<NR_PROC-1;j++){
					highP[j]=highP[j+1];
				}
				highP[j]=-1;
				highI--;
				i--;
				disp_color_str("high2mid",4);
			}
		}

		if(greatest_ticks) break;
		else{
			temp=midI;
			for(i=0;i<temp;i++){
				//再找中优先级分配处理器
				if(midP[i]!=-1 && proc_table[midP[i]].ticks>0){
					greatest_ticks=proc_table[midP[i]].ticks;
					p_proc_ready=&proc_table[midP[i]];
					break;
			    }else if(midP[i]!=-1 && proc_table[midP[i]].ticks<=0){//时间片用完的进入低优先级，并分配LOW_TICK，然后等待
					proc_table[midP[i]].ticks=LOW_TICK;
					lowP[lowI++]=midP[i];
					int j;
					for(j=i;j<NR_PROC-1;j++){
						midP[j]=midP[j+1];
					}
					midP[j]=-1;
					midI--;
					i--;
					disp_color_str("mid2low",3);
				}
			}
		}

		if(greatest_ticks) break;
		else{
			for(i=0;i<temp;i++){
				//再找低优先级分配处理器
				if(lowP[i]!=-1 && proc_table[lowP[i]].ticks>0){
					greatest_ticks=proc_table[lowP[i]].ticks;
					p_proc_ready=&proc_table[lowP[i]];
					break;
			    }else if(lowP[i]!=-1 && proc_table[lowP[i]].ticks<=0){//时间片用完,只能再分配给它LOW_TICK
					proc_table[lowP[i]].ticks=LOW_TICK;
					disp_color_str("low again",2);
				}
			}
		}
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

