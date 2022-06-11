`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2021/01/10 20:11:56
// Design Name:
// Module Name: VideoGen
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module VideoGen(
    input CLK,
    input RST,
    output reg[23:0] data_out,
    output reg hsync_out,
    output reg vsync_out,
    output reg de_out,
    input  [3:0]sw,
    output reg [3:0] led,
    output [31:0] delayclock_out,
    input   sensor_in,
    input   cleardata_in,
    input start_in,
    output reg done_out
//    output reg[31:0] delayCounter,
//    output reg[11:0] CounterX,
//    output reg[10:0] CounterY
//    output reg flg,
//    output reg count_en
    );

reg flg;
reg count_en;
reg[31:0] delayCounter;
reg[11:0] CounterX;
reg[10:0] CounterY;
 
assign delayclock_out = delayCounter;


/*Timing*/
//reg [10:0] CounterX;  // counts from 0 to 1650
always @(posedge CLK)begin
    if(RST)begin
        CounterX <= 12'h0;
    end
    if(!RST)begin
        //CounterX <= (CounterX==1650) ? 0 : CounterX+1;
        CounterX <= (CounterX==2200) ? 0 : CounterX+1;
    end
end

//reg [9:0] CounterY;  // counts from 0 to 750
always @(posedge CLK)begin
    if(RST)begin
        CounterY <= 11'h0;
    end
    if(!RST)begin
        //if(CounterX==1650) CounterY <= (CounterY==750) ? 0 : CounterY+1;
        if(CounterX==2200) CounterY <= (CounterY==1125) ? 0 : CounterY+1;
    end
end


always @(posedge CLK) begin
    if(RST)begin
        flg <= 0;
        delayCounter <= 0;
        data_out <= 0;
        led <= 4'h0;
        count_en <= 0;
        done_out <= 0;
    end else begin
        if(start_in==1)begin //measure start button
            count_en <= 1;
            led <= led | 4'b0001;
        end
    
        if(count_en==1 && CounterX==0 && CounterY==0)begin
            flg <= 1;
        end
    
        if(flg==1) begin
            data_out <= 24'hffffff;
            delayCounter <= delayCounter+1;
            led <= led | 4'b0010;
        end else if(sw[2:0]>0)begin
            data_out <= ({24{sw[0]}} & 24'h0000FF) | ({24{sw[1]}} & 24'h00FF00) |({24{sw[2]}} & 24'hFF0000);
        end else begin
            data_out <= 24'h000000;
        end
    
        if(sensor_in==0)begin //sensor detected
            flg <= 0; //display stop & count stop
            count_en <= 0;
            led <= led | 4'b0100;
            done_out <= 1;
        end
    
        if(cleardata_in==1)begin //reset state
            flg <= 0;
            delayCounter <= 0;
            count_en <= 0;
            led <= 0;
            done_out <= 0;
        end
    end
end



/*hsync = (CounterX>=1390) && (CounterX<1430)*/
always @(posedge CLK)begin
    //if((CounterX>=1390) && (CounterX<1430))
    if((CounterX>=2008) && (CounterX<2052))
        hsync_out <= 1'b1;
    else
        hsync_out <= 1'b0;
end

/*vsync = (CounterY>=725) && (CounterY<730)*/
always @(posedge CLK)begin
    //if((CounterY>=725) && (CounterY<730))
    if((CounterY>=1084) && (CounterY<1089))
        vsync_out <= 1'b1;
    else
        vsync_out <= 1'b0;
end

/*DrawArea = (CounterX<1280) && (CounterY<720)*/
always @(posedge CLK)begin
    if((CounterX<1920) && (CounterY<1080))
        de_out <= 1'b1;
    else
        de_out <= 1'b0;
end

endmodule
