#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project2.h"
 
/* ***************************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for unidirectional or bidirectional
   data transfer protocols from A to B and B to A.
   Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets may be delivered out of order.

   Compile as gcc -g project2.c student2.c -o p2
**********************************************************************/

int lastSeq; // store the previous sequence number for comparison
struct pkt lastPacket; // store copy of most recently sent packet (to resending)

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
/* 
 * The routines you will write are detailed below. As noted above, 
 * such procedures in real-life would be part of the operating system, 
 * and would be called by other procedures in the operating system.  
 * All these routines are in layer 4.
 */

/* 
 * A_output(message), where message is a structure of type msg, containing 
 * data to be sent to the B-side. This routine will be called whenever the 
 * upper layer at the sending side (A) has a message to send. It is the job 
 * of your protocol to insure that the data in such a message is delivered 
 * in-order, and correctly, to the receiving side upper layer.
 */
void A_output(struct msg message) {

    if(TraceLevel >= 2)
        printf("\nA_output called\n");

    if(TraceLevel >= 2)
        printf("Generating packet to send\n");

    struct pkt sendPacket;  // create packet

    // Packet Setup
    sendPacket.acknum = 0; // sender doesn't use ACK
    sendPacket.seqnum = !lastSeq; // opposite previous sequence number
    for (int i = 0; i < MESSAGE_LENGTH; i++) // copy message into payload
    {
        sendPacket.payload[i] = message.data[i];
    }
    sendPacket.checksum = calcChecksum(sendPacket); // Create checksum

    if(TraceLevel >= 2)
        printf("Packet populated, sending packet\n");

    tolayer3(AEntity, sendPacket); // send packet
    startTimer(AEntity, 1000); // send timer to wait for ack

    lastSeq = sendPacket.seqnum; // Update previous sequence number

    if(TraceLevel >= 2)
        printf("Packet sent, copying packet for possible resend\n");

    // Copy sent packet in event of needing to resend
    lastPacket.acknum   = sendPacket.acknum;
    lastPacket.seqnum   = sendPacket.seqnum;
    lastPacket.checksum = sendPacket.checksum;
    strcpy(lastPacket.payload, sendPacket.payload);

    if(TraceLevel >= 2)
        printf("Packet copied, end of A_output\n");
}

/* 
 * A_input(packet), where packet is a structure of type pkt. This routine 
 * will be called whenever a packet sent from the B-side (i.e., as a result 
 * of a tolayer3() being done by a B-side procedure) arrives at the A-side. 
 * packet is the (possibly corrupted) packet sent from the B-side.
 */
void A_input(struct pkt packet) {

    if(TraceLevel >= 2)
        printf("\nA_input called\n");

    stopTimer(AEntity);

    // check for packet corruption
    if(calcChecksum(lastPacket) != packet.checksum)
    {
        if(TraceLevel >= 2)
            printf("Packet is corrupt, resending\n");

        tolayer3(AEntity, lastPacket);
        startTimer(AEntity, 1000);
    }

    // if packet not corrupt -> check ACK
    else if(packet.acknum != lastPacket.seqnum)
    {
        if(TraceLevel >= 2)
            printf("Returned NAK, resending\n");

        tolayer3(AEntity, lastPacket);
        startTimer(AEntity, 1000);
    }

    // packet was received successfully
    else
    {

    }
}

/*
 * A_timerinterrupt()  This routine will be called when A's timer expires 
 * (thus generating a timer interrupt). You'll probably want to use this 
 * routine to control the retransmission of packets. See starttimer() 
 * and stoptimer() in the writeup for how the timer is started and stopped.
 */
void A_timerinterrupt() {

        // if timer expires, resend packet
        if(TraceLevel >= 2)
            printf("No response from B, resending packet");

        tolayer3(AEntity, lastPacket);
        startTimer(AEntity, 1000);
}  

/* The following routine will be called once (only) before any other    */
/* entity A routines are called. You can use it to do any initialization */
void A_init() {

    lastSeq = 1; // initial sequence number will be zero
}


/*
 * Just like A_output, but residing on the B side.  USED only when the 
 * implementation is bi-directional.
 */
void B_output(struct msg message)  { /*Not implemented for this project*/ }

/*
 * B_input(packet),where packet is a structure of type pkt. This routine 
 * will be called whenever a packet sent from the A-side (i.e., as a result 
 * of a tolayer3() being done by a A-side procedure) arrives at the B-side. 
 * packet is the (possibly corrupted) packet sent from the A-side.
 */
void B_input(struct pkt packet) {

}

/*
 * B_timerinterrupt()  This routine will be called when B's timer expires 
 * (thus generating a timer interrupt). You'll probably want to use this 
 * routine to control the retransmission of packets. See starttimer() 
 * and stoptimer() in the writeup for how the timer is started and stopped.
 */
void  B_timerinterrupt() {
    
}

/* 
 * The following routine will be called once (only) before any other   
 * entity B routines are called. You can use it to do any initialization 
 */
void B_init() {

}

/*
 * 
 *   
 */
int calcChecksum(struct pkt packet) {
    return 0;
}
