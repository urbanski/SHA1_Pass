Summary - Use SHA1 hashes generated from sentences as your passwords.

    * When authenticating, paste the password. There's no need to type it.
    * Use different sentences and words to create different passwords.

----------------------------------------------

Goals

   1. Focus on sentence based passwords.
   2. Generate passwords when needed. Do not store them.
   3. Generate passwords that have a measurable bit strength.
   4. Run locally on end-use devices. Do not run "in the cloud" or "in web browsers" or "on other people's servers".
   5. Use standard, secure hashing (SHA1) and be portable. SHA1_Pass must generate independently reproducible results.

    Note: When calculating HMAC-SHA1, the HMAC key must be the user provided input (Sentence and Word) and the HMAC 
    message must be the string constant "SHA1_Pass"

   6. SHA1_Pass is free software. As of version 1.6, SHA1_Pass is distributed solely under the GPL license.

----------------------------------------------

Benefits of Sentences

    * Sentences are natural and easy to remember.
    * Sentences have a standard, accepted structure.
    * Sentences are more resistant to guessing attacks.
    * Sentences can be easily shared with others verbally.

Benefits of SHA1

    * Should the SHA1 hash be revealed, it will protect your sentence from disclosure.
    * Cracking a unique, secure SHA1 hashed sentence is infeasible. SHA1 is 256 ^ 20.
    * If asked, you can honestly say that you do not know the password. You only know how to generate it.
    * SHA1 is a portable standard with many implementations. There is no vendor lock-in or secret encryption.

Benefits of SHA1_Pass

    * SHA1_Pass has no advertisements, no malware, no spyware, no usage tracking, no snooping on what you do or what sites you visit.
    * SHA1_Pass is a self-contained program. You can download it and run it right away. There is nothing to install.
    * SHA1_Pass is open source (GPL license). Written by 16 Systems/Brad Tilley (brad At 16s Dot us).
    * SHA1_Pass does not store passwords. There is nothing to protect or backup or reinstall.
    * Other software can reproduce SHA1_Pass results. There is no lock-in or secrets.
    * SHA1_Pass is portable. It runs on most any operating system.

----------------------------------------------

To reproduce SHA1_Pass results with OpenSSL

    * echo -n 'Your Secret Sentence.your_secret_word' | openssl dgst -sha1
    * echo -n 'Your Secret Sentence.your_secret_word' | openssl sha1 -binary | openssl base64
    * echo -n SHA1_Pass | openssl dgst -sha1 -hmac 'Your Secret Sentence.your_secret_word'
    * echo -n SHA1_Pass | openssl dgst -sha1 -binary -hmac 'Your Secret Sentence.your_secret_word' | openssl enc -base64

----------------------------------------------

Note to developers: 

	* When implementing SHA1_Pass, read the six goals (listed above) as a list of requirements.

END
