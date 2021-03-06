// CSerialPort.h

#ifndef _CSERIALPORT_h
#define _CSERIALPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "CommDef.h"
#include <SoftwareSerial.h>

///////////////////////////////////////////////////////
// <<< CSerialPort - class for Arduino Serial COM port 
///////////////////////////////////////////////////////
class CSerialPort
{
protected:
	LONG	m_lDataRate;				// Data rate for serial COM
	INT		m_nTypeOfCOM_BT;			// Type of Arduino COM of Bluetooth modem: 0-Hardware COM (RX=0, TX=1), 1-Software  
	INT		m_nRX_PIN;					// Software UART RX pin, connect to TX of Bluetooth modem
	INT		m_nTX_PIN;					// Software UART TX pin, connect to RX of Bluetooth modem
	BYTE	m_bContactByte;				// Byte for establish contact with remote side
	UINT	m_nSendContactByteDelay;	// Delay in mls before repeat send byte
	LONG	m_lSerialTimeout;			// Maximum milliseconds to wait for serial data when using Read(BYTE*)

	SoftwareSerial* m_pSSerial;			// SoftwareSerial COM

public:
	// Names of types of Bluetooth modem's COM port
	enum TypeCOMofBT{isCOMofBT_Hardware=0, isCOMofBT_Software = 1};

	// Constructor, destructor
	CSerialPort(INT nTypeCOM, INT nRX, INT nTX);
	~CSerialPort() { }
	
	// --- MODIFYING methods
	// Initialisation of SerialPort
	void Init(LONG lDR_COM, BYTE b, UINT nDelay = 500, LONG lTimeOut = 1000);

	// Set the maximum milliseconds to wait for serial data when using Read(BYTE*)
	void SetReadTimeout(LONG lTimeout) { m_lSerialTimeout = lTimeout; }

	// --- CONSTANT methods
	// Sends a byte with the special value and repeats that until it gets a serial response from the remote sidee. 
	void EstablishContact() const;
	
	// Read byte from COM port
	// Return:	-1	- no byte read, else - reading byte 	
	INT Read() const;
	// Read data from COM port into byte array. First byte = SIZE of data, array must be [SIZE+1]. 
	// Return:	>0 - size of byte array, 
	//			-1 - no bytes available in port,
	//			-2 - not all bytes read, data must be re-read,
	//			-3 - data size is big.
	INT Read(BYTE *pBuffer, INT nMaxBuffLen = 256) const;

	// Write byte into COM port
	void Write(BYTE bData) const;
	// Write bytes from array into COM port
	void Write(BYTE *pBuffer, INT nLength) const;
};
#endif

