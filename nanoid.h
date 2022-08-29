#ifndef My_Nanoid_Hdr
#define My_Nanoid_Hdr

extern void nanoid_(const unsigned char* a,
                    unsigned aLen,
                    unsigned size,
                    unsigned char* randomBytes,
                    unsigned char* ret);

extern unsigned intId(void);
extern unsigned long bigintId(void);

#endif
