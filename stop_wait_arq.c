#include <stdio.h>
#include <stdlib.h>
float t_time, p_time;
int N;
int main()
{
printf("Enter number of packets to send\n");
scanf("%d", &N);
printf("Enter transmission time\n");
scanf("%f", &t_time);
printf("Enter propagation time\n");
scanf("%f", &p_time);
float var = 0;
printf("Sending %d packets with transmission time: %.0fms and
propagation time: %.0fms using stop and wait protocol\n", N, t_time,
p_time);
for (int i = 0; i < N; i++)
{
printf("Sending packet %d....\n", i + 1);
var += t_time;
printf("Packet %d sent at %.2f ms\n", i + 1, var);
var += p_time;
printf("Packet %d received at %.2f ms\n", i + 1, var);
printf("Packet received!!!\n");
var += t_time;
printf("Acknowledgment for packet %d sent at %.2f ms\n", i + 1,
var);
var += p_time;
printf("Acknowledgment received by sender for packet %d at %.2f
ms\n", i + 1, var);
}
return 0;
}
