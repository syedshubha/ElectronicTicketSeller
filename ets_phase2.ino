#include <LiquidCrystal.h>
///description of circuit connection
const int rs=8, en=9 ,db4=4 ,db5=5, db6=6, db7=7; 
const int Reset=21,Exit=20, Confirm=19, Cancel=17, Next=15 ;
const int Digit1=23,Digit2=24,Digit3=25,Digit4=26,Digit5=27,Digit6=28,Digit7=29,Digit8=30,Digit9=31;
const int Ticket_out=13;
///declaration of variables
const int TC_balance=2000;
int reset, exitt, confirm, cancel, next, digit1,digit2,digit3,digit4,digit5,digit6,digit7,digit8,digit9;
int  total_fare, route, balance, wanted_ticket; 
//int state2,state3a,state3b,state6a,state6b;//present stateA--former state2, stateB---state3a, stateC---state3b, stateD---state6a,stateE---state6b
int stateA,stateB,stateC,stateD,stateE;
int available_ticket, available_ticket1,available_ticket2,available_ticket3,available_ticket4,available_ticket5,available_ticket6,available_ticket7,available_ticket8,available_ticket9;
int digit; 
LiquidCrystal lcd(rs, en, db4, db5, db6, db7);

void setup() {
  // put your setup code here, to run once:
pinMode(Reset,INPUT);
pinMode(Exit,INPUT);
pinMode(Confirm,INPUT);
pinMode(Cancel,INPUT);
pinMode(Next,INPUT);
pinMode(Digit1,INPUT);
pinMode(Digit2,INPUT);
pinMode(Digit3,INPUT);
pinMode(Digit4,INPUT);
pinMode(Digit5,INPUT);
pinMode(Digit6,INPUT);
pinMode(Digit7,INPUT);
pinMode(Digit8,INPUT);
pinMode(Digit9,INPUT);
pinMode(Ticket_out,OUTPUT);
Serial.begin(9600);
lcd.begin(40,2);// a 40 x 2 LCD has been used in Proteus circuit  
delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
reset=digitalRead(Reset);
exitt=digitalRead(Exit);
confirm=digitalRead(Confirm);
cancel=digitalRead(Cancel);
next=digitalRead(Next);
digit1=digitalRead(Digit1);
digit2=digitalRead(Digit2);
digit3=digitalRead(Digit3);
digit4=digitalRead(Digit4);
digit5=digitalRead(Digit5);
digit6=digitalRead(Digit6);
digit7=digitalRead(Digit7);
digit8=digitalRead(Digit8);
digit9=digitalRead(Digit9);
digit=digit1+2*digit2+3*digit3+4*digit4+5*digit5+6*digit6+7*digit7+8*digit8+9*digit9;
    if (exitt)//To start, press reset
    {
      //if (state1)                               ///edit1
      //{
      //start of task Flush_memory
      ////message_no=0;
      ////ticket_out=0;
      digitalWrite(Ticket_out,LOW);
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
      
      ////message_no=1;//Select your destination
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Select your Destination (Press a digit ");
      lcd.setCursor(0,1);
      lcd.print("from 1 to 9)");
      delay(100);
      

      stateA=1; 
      //}                                               ///edit1
    }


  if(digit>0)
    {
      if(stateA)
      {
        stateA=0;
        route=digit; 
      
        switch(route)
        {
          case 1:  available_ticket=available_ticket1; break;
          case 2:  available_ticket=available_ticket2; break;
          case 3:  available_ticket=available_ticket3; break;
          case 4:  available_ticket=available_ticket4; break;
          case 5:  available_ticket=available_ticket5; break;
          case 6:  available_ticket=available_ticket6; break;
          case 7:  available_ticket=available_ticket7; break;
          case 8:  available_ticket=available_ticket8; break;
          case 9:  available_ticket=available_ticket9; break;
        }
        
        if(!available_ticket)
        {

          ////message_no=2;//Sorry! All tickets in this route have been sold. Press exit to return to previous window.

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Sorry! All tickets in this route have ");
          lcd.setCursor(0,1);
          lcd.print("been sold. Press exit.");
          delay(100);
        } 
      
        else
        {
          stateB=1;
          ////message_no=3;//No. of Tickets available for this route _ _ _.Press next to buy tickets.
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Tickets available for this route  ");
          lcd.print(available_ticket);
          lcd.setCursor(0,1);
          lcd.print(".Press next to buy tickets.");
          delay(100);
  
        }
      }
      
      else if(stateC)
      {
        stateC=0;
        wanted_ticket=digit;  
      
        if(available_ticket<wanted_ticket)
        {       
          //state4=1;
          ////message_no=10;//Press next to proceed
          
          //lcd.clear();
          //lcd.setCursor(0,0);
          //lcd.print("Press next to proceed");
          //delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("You entered a number greater than ");
          lcd.setCursor(0,1);
          lcd.print("available tickets, Press cancel.");
          delay(100);
          
          stateB=1;
        }
      
        else
        {
          //state5=1;
          ////message_no=10;//Press next to proceed

          //lcd.clear();
          //lcd.setCursor(0,0);
          //lcd.print("Press next to proceed");
          //delay(1000);
            switch(route)
          {
            case 1:total_fare= 500 * wanted_ticket; break; //500 is the fare for route 1
            case 2:total_fare= 400 * wanted_ticket; break; //400 is the fare for route 2
            case 3:total_fare= 800 * wanted_ticket; break; //800 is the fare for route 3
            case 4:total_fare= 950 * wanted_ticket; break; //950 is the fare for route 4
            case 5:total_fare= 650 * wanted_ticket; break; //650 is the fare for route 5
            case 6:total_fare= 700 * wanted_ticket; break; //700 is the fare for route 6
            case 7:total_fare= 200 * wanted_ticket; break; //200 is the fare for route 7
            case 8:total_fare= 120 * wanted_ticket; break; //120 is the fare for route 8
            case 9:total_fare= 300 * wanted_ticket; break; //300 is the fare for route 9
          }
          
          stateD=1;
          ////message_no=6;//The tickets will cost _ _ _ Taka. Are you sure to buy tickets? Press Confirm or Cancel.
  
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("The tickets will cost ");
          lcd.print(total_fare);
          lcd.print("Taka. Are ");
          lcd.setCursor(0,1);
          lcd.print("you sure? Press Confirm or Cancel.");
          delay(100);
          }
       
      }

    }

    if (next)
    {
      if(stateB)
      {
        ////message_no=4;//How many tickets do you want to buy?(Press a digit between 1 and 9)

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("How many tickets do you want to buy?");
        lcd.setCursor(0,1);
        lcd.print("(Press a digit between 1 and 9)");
        delay(100);
        
        stateB=0;
        stateC=1;
      }
      

      

    }

    if (cancel)
    {
      if (stateB | stateD | stateE)
      {
        stateB=0;
        stateD=0;
        stateE=0;
        stateC=1;
        ////message_no=4;//How many tickets do you want to buy?(Press a digit between 1 and 9)
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("How many tickets do you want to buy?");
        lcd.setCursor(0,1);
        lcd.print("(Press a digit between 1 and 9)");

        delay(100);
      }
      
    }

    
    if (confirm)
    {
      if (stateD)
      {
        stateD=0;
        stateE=1;
        ////message_no=7;//Please insert your Travel Card and Press Confirm

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Please insert your Travel Card and");
        lcd.setCursor(0,1);
        lcd.print(" Press Confirm");
        delay(100);
        
      }
      
      else if (stateE)
      {
        stateE=0;
        balance=TC_balance;//TC_balance is the current travel card balance
        
        if(balance<total_fare)
        {
          //state7=1;
          ////message_no=10;//Press next to proceed
          //lcd.clear();
          //lcd.setCursor(0,0);
          //lcd.print("Press next to proceed");
          //delay(1000); 
          stateB=1; 
        ////message_no=8;//You do not have sufficient balance. Press cancel to input no of tickets again.

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("You do not have sufficient balance.");
          lcd.setCursor(0,1);
          lcd.print(" Press cancel.");
          delay(100);         
        }
        
        else
        {
          //state8=1;
          ////message_no=10;//Press next to proceed
          //lcd.clear();
          //lcd.setCursor(0,0);
          //lcd.print("Press next to proceed");
          //delay(1000); 
          balance=balance-total_fare;// balance will store the new travel card balance
          available_ticket=available_ticket-wanted_ticket;
          
          switch(route)
          {
            case 1:  available_ticket1=available_ticket; break;
            case 2:  available_ticket2=available_ticket; break;
            case 3:  available_ticket3=available_ticket; break;
            case 4:  available_ticket4=available_ticket; break;
            case 5:  available_ticket5=available_ticket; break;
            case 6:  available_ticket6=available_ticket; break;
            case 7:  available_ticket7=available_ticket; break;
            case 8:  available_ticket8=available_ticket; break;
            case 9:  available_ticket9=available_ticket; break;
          }
          
          ////ticket_out=1;
          digitalWrite(Ticket_out,HIGH);

          ////message_no=9;//Your purchase was successful.Please collect your travel card & ticket.Press exit to complete the process.
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Your purchase was successful.");
          lcd.setCursor(0,1);        
          lcd.print("Your previous balance was ");
          lcd.print(TC_balance);
          lcd.print(" Tk.");
          delay(500);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" and current balance is ");
          lcd.setCursor(0,1);
          lcd.print(balance);
          lcd.print(" Tk.");
          delay(500);
  
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Please collect your travel card & ");
          lcd.setCursor(0,1);
          lcd.print(" tickets.Press exit.");
          delay(100);         
        }
      }
    }

    if (reset)
    {
      available_ticket1=50;
      available_ticket2=50;
      available_ticket3=50;
      available_ticket4=50;
      available_ticket5=50;
      available_ticket6=50;
      //available_ticket7=50;
      //available_ticket8=50;
      available_ticket7=0;//just for demonstration
      available_ticket8=5;//just for demonstration
      available_ticket9=50;
  
      
      //if (state1)                                ///edit2
      //{
        //start of task Flush_memory
        ////message_no=0;
        ////ticket_out=0;
        digitalWrite(Ticket_out,LOW);
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
        
        ////message_no=1;//Select your destination
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Select your Destination (Press a digit ");
        lcd.setCursor(0,1);
        lcd.print("from 1 to 9)");
        delay(100);
          

        stateA=1;
      //}                                  ///edit2
    
    }




}
