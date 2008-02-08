/*
 *  Copyright (C) 2007-2008  ZioNz - zionztp@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <wx/wx.h>
#include "lsearchFrm.h"
#include "mem_util.h"

#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_BLOCK_SIZE 200*1024*1024 //200MB

//Pointer to access main frame
extern lsearchFrm *main_frame;

//Helpers
bool find_str(string datos, string buscar){
    int i=0;
    int bt=buscar.size();
    
    while(i+bt < datos.size()){
        if(datos.substr(i,bt) == buscar){
            return true;
        }
        i++;
    }
    
    return false;
}

//Read and store all the memory of the process
bool Cmemutil::SaveMemory(int pid)
{
	Tmemblock mb;
	char line[2048];
	char fname[1024];
	string sline,a,b;
	unsigned int i;
	unsigned int max_mem = 0;
	unsigned int block_size;
	unsigned int t;
	int progress=0;
	unsigned int memcount=0;
	int tmp;
	FILE *entrada;

	//Read the mem maps
	sprintf(fname, "/proc/%i/maps", pid);
	entrada = fopen(fname, "rb");
	if(!entrada){
		return false;
	}

	FreeMemBlocks();

	do{
		fgets(line, 2000, entrada);

		//Skip libraries and others
		if(!find_str(line, "/lib/") && !find_str(line, "/dev")){
			sline = line;
			a = sline.substr(0,8);
			b = sline.substr(9,8);
            mb.start = strtoll(a.c_str(), NULL, 16); 
            mb.end = strtoll(b.c_str(), NULL, 16);
			memblocks.push_back(mb);
		}else{
			//printf("SKIP!\n");
		}
	}while(!feof(entrada));


	//Calculate total memory to read
	for(i=0; i<memblocks.size(); i++){
		block_size = memblocks[i].end - memblocks[i].start;
		max_mem += block_size;
	}

	size = max_mem;

	if(ptrace(PTRACE_ATTACH, pid, NULL, NULL)!=0){
		return false;
	}
	wait(NULL);

	//Fill memory blocks
	for(i=0; i<memblocks.size(); i++){
		block_size = memblocks[i].end - memblocks[i].start;
		if(block_size < 1 || block_size > MAX_BLOCK_SIZE){
			return false;
		}
		memblocks[i].size = block_size;

		memblocks[i].data = (char*) malloc(block_size);
		//Read memblock	
		for(t=0; t<=block_size; t+=4){
			tmp = ptrace(PTRACE_PEEKDATA, pid, memblocks[i].start + t, NULL);
			memcpy(&memblocks[i].data[t], &tmp, 4); 
/*
			memblocks[i].data[t] = (char) (tmp);
			memblocks[i].data[t+1] = (char) (tmp >> 8);
			memblocks[i].data[t+2] = (char) (tmp >> 16);
			memblocks[i].data[t+3] = (char) (tmp >> 24);
*/
			memcount+=4;
		
			if( (memcount % 100000) == 0){
				wxYield();
				progress = (50 * memcount) / max_mem;
				main_frame->Wxgauge1->SetValue(progress);
			}
		}

		printf("%02i - %p to %p , size: %d\n", i, memblocks[i].start, memblocks[i].end, memblocks[i].end - memblocks[i].start);
	}

	ptrace(PTRACE_DETACH, pid, NULL, NULL);
	return true;	
}


void Cmemutil::FreeMemBlocks()
{
	unsigned int i;

	for(i=0; i<memblocks.size(); i++){
		free(memblocks[i].data);
	}

	memblocks.clear();
}
