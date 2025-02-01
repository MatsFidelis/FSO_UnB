#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>

typedef struct Process {
	unsigned int id, i;
	std::vector<int> instruction;
}Process;

int main() {
	unsigned int n, instruction, acc = 0;
	scanf("%d", &n);
	Process *p = (Process *)malloc(sizeof(Process) * n);
	std::queue<Process> pqueue;
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i].i);
		p[i].id = i+1;
	} for (int i = 0; i < n; i++) {
		for (int j = 0; j < p[i].i; j++) {
			scanf("%d", &instruction);
			p[i].instruction.push_back(instruction);
		}
		pqueue.push(p[i]);
	} while (!pqueue.empty()) {
		int i = 0;
		Process cp = pqueue.front();
		pqueue.pop();
		while (cp.i != 0 and cp.instruction[i] != 1)
			cp.i--, acc += 10, i++;
		if (!cp.i) printf("%d (%d)\n", cp.id, acc);
		else {
			cp.instruction[i] = 0;
			for (int j = 0; j < cp.i; j++)
				cp.instruction[j] = cp.instruction[i++];
			pqueue.push(cp);
		}
	} for (int i = 0; i < n; i++) 
		p[i].instruction.clear();
	free(p);
	return 0;
}