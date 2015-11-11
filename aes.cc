#include <iostream>
#include <fstream>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
using namespace std;

int main(int argc, char **argv) {
	const unsigned KEY_LENGTH = 32;
	const unsigned BLOCKSIZE = 16;

        unsigned char key[ KEY_LENGTH ], iv[ BLOCKSIZE ];
        memset( key, 0x00, KEY_LENGTH );
        memset( iv, 0x00, BLOCKSIZE );

        for (int i=0 ; i<KEY_LENGTH ; ++i)
                key[i] = ('0' + (i%10) ) ;

        std::cout << "block size: " << BLOCKSIZE << std::endl;
        std::cout << "key(" << KEY_LENGTH << "):[";
	for(unsigned int x=0; x<KEY_LENGTH; x++)
		std::cout << key[x];
	std::cout << "]" << std::endl;

        std::string plaintext = "Hello world. To man to be a better man.";
        std::string ciphertext;

        // enc
        CryptoPP::AES::Encryption aesEncryption(key, KEY_LENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
        stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length());
        stfEncryptor.MessageEnd();

        std::ofstream output ("/tmp/output");
        output << ciphertext ;
        output.close();

        // dec
        std::string decryptedtext;
        CryptoPP::AES::Decryption aesDecryption(key, KEY_LENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
        stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
        stfDecryptor.MessageEnd();

        std::cout << "dec: [" << decryptedtext << "]" << std::endl;

        return 0;
}
