Summary - Use SHA1 hashes generated from sentences as your passwords.

    * As best practice, use the longest password acceptable and prefer base64 encoding over hex.
    * When authenticating, paste the password. There's no need to type it manually.
    * Use different sentences to create different passwords.
    * All you need to do is remember your sentences.

----------------------------------------------

Goals

   * Focus on sentence based passwords.
   * Generate passwords when needed. Do not store passwords.
   * Run locally on end-use devices. Do not run "in the cloud" or "in web browsers" or "on other people's servers".
   * Use standard, secure hashing (SHA1) and be portable. SHA1_Pass must generate independently reproducible results.
   * Use the ISC license to encourage others to use, modify and implement SHA1_Pass.

----------------------------------------------

Benefits of Sentences

    * Sentences are natural and easy to remember.
    * Sentences have a standard, accepted structure.
    * Sentences are more resistant to guessing attacks.
    * Sentences can be easily shared with others verbally.

Benefits of SHA1

    * Should the SHA1 hash be revealed, it will protect your sentence from disclosure.
    * Cracking a unique, secure SHA1 hashed sentence is infeasible. Hex encoded SHA1 is 16^40.
    * If asked, you can honestly say that you do not know the password. You only know how to generate it.
    * SHA1 is a portable standard with many implementations. There is no vendor lock-in or secret encryption.

Benefits of SHA1_Pass

    * SHA1_Pass has no advertisements, no malware, no spyware, no usage tracking, no snooping on what you do or what sites you visit.
    * SHA1_Pass is a self-contained program. You can download it and run it right away. There is nothing to install.
    * SHA1_Pass is open source (ISC license). Written by 16 Systems/Brad Tilley (brad At 16s Dot us).
    * SHA1_Pass does not store passwords. There is nothing to protect or backup or reinstall.
    * Other software can reproduce SHA1_Pass results. There is no lock-in or secrets.
    * SHA1_Pass is portable. It runs on most any operating system.

----------------------------------------------

To reproduce SHA1_Pass results with OpenSSL

    * echo -n 'Your Secret Sentence' | openssl dgst -sha1
    * echo -n 'Your Secret Sentence' | openssl sha1 -binary | openssl base64

----------------------------------------------

Note to developers: 

	* When implementing SHA1_Pass, read the goals (listed above) as a specification or list of requirements. 

END
