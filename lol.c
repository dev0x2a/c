struct lol {
  union {
    struct {
      unsigned int c:23, b:8, a:1;
    } f;
    float g;
  } data;
};

