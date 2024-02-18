

  /**
   * @desc    Write color pixels
   *
   * @param   struct st7735 *
   * @param   uint16_t
   * @param   uint16_t
   *
   * @return  void
   */
  void ST7735_SendColor565 (struct st7735 *, uint16_t, uint16_t);

  /**
   * @desc    Draw pixel
   *
   * @param   struct st7735 *
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint16_t
   * 
   * @return  void
   */
  void ST7735_DrawPixel (struct st7735 *, uint8_t, uint8_t, uint16_t);

  /**
   * @desc    Clear screen
   *
   * @param   struct st7735 *
   * @param   uint16_t
   *
   * @return  void
   */
  void ST7735_ClearScreen (struct st7735 *, uint16_t);

  /**
   * @desc    RAM Content Show
   *
   * @param   struct st7735 *
   *
   * @return  void
   */
  void ST7735_RAM_Content_Show (struct st7735 *);

  /**
   * @desc    RAM Content Hide
   *
   * @param   struct st7735 *
   *
   * @return  void
   */
  void ST7735_RAM_Content_Hide (struct st7735 *);

  /**
   * @desc    Display ON
   *
   * @param   struct st7735 * lcd
   *
   * @return  void
   */
  void ST7735_DisplayOn (struct st7735 *);

  /**
   * @desc    Check text position x, y
   *
   * @param   unsigned char
   * @param   unsigned char
   * @param   unsigned char
   *
   * @return  char
   */
  char ST7735_CheckPosition (unsigned char, unsigned char, unsigned char, enum Size);

  /**
   * @desc    Set text position x, y
   *
   * @param   uint8_t
   * @param   uint8_t
   *
   * @return  char
   */
  char ST7735_SetPosition (uint8_t, uint8_t);

  /**
   * @desc    Draw character
   *
   * @param   struct st7735 *
   * @param   char
   * @param   uint16_t
   * @param   enum Size (X1, X2, X3)
   *
   * @return  void
   */
  char ST7735_DrawChar (struct st7735 *, char, uint16_t, enum Size);

  /**
   * @desc    Draw string
   *
   * @param   struct st7735 *
   * @param   char *
   * @param   uint16_t
   * @param   enum Size (X1, X2, X3)

   * @return void
   */
  void ST7735_DrawString (struct st7735 *, char *, uint16_t, enum Size);

  /**
   * @desc    Draw line
   *
   * @param   struct st7735 *
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint16_t
   *
   * @return void
   */
  char ST7735_DrawLine (struct st7735 *, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);

  /**
   * @desc    Fast draw line horizontal
   *
   * @param   struct st7735 *
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint16_t
   *
   * @return  void
   */
  void ST7735_DrawLineHorizontal (struct st7735 *, uint8_t, uint8_t, uint8_t, uint16_t);

  /**
   * @desc    Fast draw line vertical
   *
   * @param   struct st7735 *
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint16_t
   *
   * @return  void
   */
  void ST7735_DrawLineVertical (struct st7735 *, uint8_t, uint8_t, uint8_t, uint16_t);

  /**
   * @desc    Draw rectangle
   *
   * @param   struct st7735 *
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint8_t
   * @param   uint16_t
   *
   * @return  void
   */
  void ST7735_DrawRectangle (struct st7735 *, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);

