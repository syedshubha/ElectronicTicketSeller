module ets_v2(reset,confirm,cancel,exit,clock,next,digit,TC_balance,message_no,balance,ticket_out,total_fare,wanted_ticket,route,available_ticket);
	
	input reset,confirm,cancel,exit,clock,next;
	input [1:9]digit; 
	input [15:0]TC_balance;
	output reg [3:0]message_no;
	output reg [15:0]balance;
	output reg ticket_out;
	
	//reg state2,state3a,state3b,state6a,state6b;//now stateA was former state2, now stateB was former state3a, stateC was state3b, stateD---state6a,stateE---state6b
	reg stateA,stateB,stateC,stateD,stateE;
	output reg [5:0]available_ticket;
	reg [5:0] available_ticket1,available_ticket2,available_ticket3,available_ticket4,available_ticket5,available_ticket6,available_ticket7,available_ticket8,available_ticket9;
	output reg [3:0]wanted_ticket,route;
	output reg [15:0]total_fare;
	


	//always @(posedge |digit[1:9], posedge reset, posedge confirm, posedge cancel, posedge exit, posedge clock, posedge next)
	//the above line creates error while simulating in simulator tool
	always@(posedge clock)//now all the operations are synchronous, so the user has to input any command by making the command value High at the positive edge of clock
		begin
		if (exit)//To start, press reset
		begin

			//start of task Flush_memory
			message_no=0;
			ticket_out=0;
			balance=0;

			stateA=0;
			stateB=0;
			stateC=0;

			stateD=0;
			stateE=0;

			wanted_ticket=0;
			route=0;
			total_fare=0;
			available_ticket=0;
			//end of task Flush_memory
			
			message_no=1;//Select your destination
			stateA=1;

		end
		
		if(|digit)
		begin
			if(stateA)
			begin
				stateA=0;
				case(digit)
					9'b 100_000_000: route=1;
					9'b 010_000_000: route=2;
					9'b 001_000_000: route=3;
					9'b 000_100_000: route=4;
					9'b 000_010_000: route=5;
					9'b 000_001_000: route=6;
					9'b 000_000_100: route=7;
					9'b 000_000_010: route=8;
					9'b 000_000_001: route=9;
				endcase  
				
				case(route)
					1:	available_ticket=available_ticket1;
					2:	available_ticket=available_ticket2;
					3:	available_ticket=available_ticket3;
					4:	available_ticket=available_ticket4;
					5:	available_ticket=available_ticket5;
					6:	available_ticket=available_ticket6;
					7:	available_ticket=available_ticket7;
					8:	available_ticket=available_ticket8;
					9:	available_ticket=available_ticket9;
				endcase
				
				if(!available_ticket)
				begin

					message_no=2;//Sorry! All tickets in this route have been sold. Press exit to return to previous window.

				end	
			
				else
				begin
					stateB=1;
					message_no=3;//No. of Tickets available for this route _ _ _.Press next to buy tickets.

				end
			end
			
			else if(stateC)
			begin
				stateC=0;
				case(digit)
				9'b 100_000_000: wanted_ticket=1;
				9'b 010_000_000: wanted_ticket=2;
				9'b 001_000_000: wanted_ticket=3;
				9'b 000_100_000: wanted_ticket=4;
				9'b 000_010_000: wanted_ticket=5;
				9'b 000_001_000: wanted_ticket=6;
				9'b 000_000_100: wanted_ticket=7;
				9'b 000_000_010: wanted_ticket=8;
				9'b 000_000_001: wanted_ticket=9;
				endcase  
			
				if(available_ticket<wanted_ticket)
				begin				
					//state4=1;
					//message_no=10;//Press next to proceed
					message_no=5;//You entered a number greater than available tickets, Press cancel to input no of tickets again
					stateB=1;
				end
			
				else
				begin
					//state5=1;
					//message_no=10;//Press next to proceed
					case(route)
						1:total_fare= 500 * wanted_ticket;//500 is the fare for route 1
						2:total_fare= 400 * wanted_ticket;//400 is the fare for route 2
						3:total_fare= 800 * wanted_ticket;//800 is the fare for route 3
						4:total_fare= 950 * wanted_ticket;//950 is the fare for route 4
						5:total_fare= 650 * wanted_ticket;//650 is the fare for route 5
						6:total_fare= 700 * wanted_ticket;//700 is the fare for route 6
						7:total_fare= 200 * wanted_ticket;//200 is the fare for route 7
						8:total_fare= 120 * wanted_ticket;//120 is the fare for route 8
						9:total_fare= 300 * wanted_ticket;//300 is the fare for route 9
					endcase
					
					stateD=1;
					message_no=6;//The tickets will cost _ _ _ Taka. Are you sure to buy tickets? Press Confirm or Cancel.

					
				end
			end
		end
		
		if (next)
		begin
			if(stateB)
			begin
				message_no=4;//How many tickets do you want to buy?(Press a digit between 1 and 9)
				stateB=0;
				stateC=1;
			end
			
		end
		
		if (cancel)
		begin
			if (stateB | stateD | stateE)
			begin
				stateB=0;
				stateD=0;
				stateE=0;
				stateC=1;
				message_no=4;//How many tickets do you want to buy?(Press a digit between 1 and 9)

			end
			
		end
		
		if (confirm)
		begin
			if (stateD)
			begin
				stateD=0;
				stateE=1;
				message_no=7;//Please insert your Travel Card and Press Confirm

			end
			
			else if (stateE)
			begin
				stateE=0;
				balance=TC_balance;//TC_balance is the current travel card balance
				
				if(balance<total_fare)
				begin
					//state7=1;
					//message_no=10;//Press next to proceed
					stateB=1; 
					message_no=8;//You do not have sufficient balance. Press cancel to input no of tickets again.

				end
				
				else
				begin
					//state8=1;
					//message_no=10;//Press next to proceed
					balance=balance-total_fare;// balance will store the new travel card balance
					available_ticket=available_ticket-wanted_ticket;
					
					case(route)
						1:	available_ticket1=available_ticket;
						2:	available_ticket2=available_ticket;
						3:	available_ticket3=available_ticket;
						4:	available_ticket4=available_ticket;
						5:	available_ticket5=available_ticket;
						6:	available_ticket6=available_ticket;
						7:	available_ticket7=available_ticket;
						8:	available_ticket8=available_ticket;
						9:	available_ticket9=available_ticket;
					endcase
					
					ticket_out=1;

					message_no=9;//Your purchase was successful.Please collect your travel card & ticket.Press exit to complete the process.
				end
			end
		end
		
		if (reset)
		begin
			//available_ticket={9{6'b 110010}};//110010 in binary converts into 50 in decimal which is the total seat number for each route
			available_ticket1=50;
			available_ticket2=50;
			available_ticket3=50;
			available_ticket4=50;
			available_ticket5=50;
			available_ticket6=50;
			available_ticket7=50;
			available_ticket8=50;
			available_ticket9=50;
			

			message_no=0;
			ticket_out=0;
			balance=0;

			stateA=0;
			stateB=0;
			stateC=0;

			stateD=0;
			stateE=0;

			wanted_ticket=0;
			route=0;
			total_fare=0;
			available_ticket=0;
			//end of task Flush_memory
			
			message_no=1;//Select your destination

			stateA=1;
			//end
		end
	end
endmodule	
