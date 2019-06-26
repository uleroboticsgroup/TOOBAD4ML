int main(){
    char buf[32];
    char* str;
    /* 32 + "<>" + NUL = 35, allowing 3
    bytes of overflow */
    sprintf(buf, "<%.32s>", str);
    sprintf(buf, "<%.15s>", str);

    char name[5] = "AAAA";
    name[5] = 'A';
}

/// ###BEGIN_VULNERABLE_LINES###

/// 6,5;6,32

/// 7,5;7,32

/// 10,5;10,15
