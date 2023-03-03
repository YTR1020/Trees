# Readme

## 信息论与编码-课设

1.算术编码的编码与译码：

要求：输入字符集为{a,b},且 p(a)=1/4,p(2)=3/4.对长度 L<=60（至少 30）的序列进行算
术编码,并进行反向译码

输入文件:in1.txt，含至少两组输入，每组为满足要求的串 

输出文件:out1.txt，对每组输入的编码和译码结果




3.综合编码 1：游程编码+Huffman 编码+加密编码+信道编码及对应的译码

一个二元无记忆信源，0 符号的出现概率为 1/4, 1 符号的出现概率为 3/4。

现要求对该信源连续出现的 n 个符号序列，进行游程编码/对游程编码结果进行 Huffman 编码（可用教材的 MH 编码方案）/使用加密算法进行加密/进行信道编码；

然后模拟信道的传输过程，并对收到的信息串进行信道译码/解密译码/Huffman 译码/游程译码。

假定，连续出现的 0 或 1 序列的长度不超过 16，n 不小于 256。

其中加密编码/解密译码可自主选择对称加密算法或非对称算法；

信道编码要求采用(7,4)系统循环码,其中,g(x)= x3+x+1，译码采用简化的译码表；

信道为 BSC 信道，p=10-2

输入：长为 n 的 0/1 串

输出：1. 游程编码结果，2. Huffman 编码结果，3. 加密编码结果 4. 信道编码结果
5. 模拟接收串，6. 信道译码结果，7. 解密编码结果 8. Huffman 译码结果
9. 游程译码结果

输入文件:in3.txt，含至少两组输入

输出文件:out3.txt，对每组输入的处理结果