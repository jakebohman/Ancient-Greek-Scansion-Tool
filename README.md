# Ancient Greek Scansion
This project is a useful tool for those who wish to quickly scan Ancient Greek poetry. For each line pasted into the program, it will determine whether the line fits the selected meter and output the estimated scansion.

**Supported meters**
* Dactylic Hexameter
* Elegiac Couplet
* Dactylic Pentameter

**Known issues**

While the scanner is correct in the majority of cases (96/100 of the Odyssey's opening lines), any errors are likely due to one of these factors:
* The program currently is unable to distinguish between ᾰ, ῐ, ῠ and long-by-nature ᾱ, ῑ, ῡ.
* I had to input every possible vowel and dipthong manually, so some obscure ones are likely missing.
* The scanner has a hard time with synizesis (for example, determing whether 'εω' is one or two syllables).
Coincidentally and unfortunately, the opening lines of the Iliad experience these issues quite frequently.

**Future features**
* Fixes to the issues mentioned above.
* Ability to analzye diaereses, caesurae, and other metrical features.
* Support for other meters such as iambic trimeter and trochaic tetrameter.


You are free to copy, modify, and/or distribute this software for any purpose, subject to the terms of the MIT License.
