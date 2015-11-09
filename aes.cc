#include <iostream>
#include <fstream>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

int main(int argc, char **argv) {
        byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
        memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

        for (int i=0 ; i<CryptoPP::AES::DEFAULT_KEYLENGTH ; ++i)
                key[i] = ('0' + (i%10) ) ;

        std::cout << "block size: " << CryptoPP::AES::BLOCKSIZE << std::endl;
        std::cout << "key(" << CryptoPP::AES::DEFAULT_KEYLENGTH << "):[" << key << "]" << std::endl;

        std::string plaintext = "Hello world. To man to be a better man.";
        std::string ciphertext;

        // enc
        CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
        stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length());
        stfEncryptor.MessageEnd();

        std::ofstream output ("/tmp/output");
        output << ciphertext ;
        output.close();

        // dec
        std::string decryptedtext;
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
        stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
        stfDecryptor.MessageEnd();

        std::cout << "dec: [" << decryptedtext << "]" << std::endl;

        return 0;
}
