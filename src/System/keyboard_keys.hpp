#pragma once
#include <stdint.h>

// These values map with GLFW keys
enum class Key:uint16_t{
    // Printable keys
    Space         = 32,
    Apostrophe    = 39, 
    Comma         = 44,
    Minus         = 45,
    Period        = 46,
    Slash         = 47, /* / */
    
    // Numbers
    D_0            = 48,
    D_1            = 49,
    D_2            = 50,
    D_3            = 51,
    D_4            = 52,
    D_5            = 53,
    D_6            = 54,
    D_7            = 55,
    D_8            = 56,
    D_9            = 57,
    
    Semicolon     = 59,
    Equal         = 61,
    
    // Letters
    A             = 65,
    B             = 66,
    C             = 67,
    D             = 68,
    E             = 69,
    F             = 70,
    G             = 71,
    H             = 72,
    I             = 73,
    J             = 74,
    K             = 75,
    L             = 76,
    M             = 77,
    N             = 78,
    O             = 79,
    P             = 80,
    Q             = 81,
    R             = 82,
    S             = 83,
    T             = 84,
    U             = 85,
    V             = 86,
    W             = 87,
    X             = 88,
    Y             = 89,
    Z             = 90,
    
    Left_Bracket   = 91,  /* [ */
    Backslash     = 92,  /* \ */
    Right_Bracket  = 93,  /* ] */
    Grave_Accent   = 96,  /* ` */
    
    // Function keys
    Esc        = 256,
    Enter         = 257,
    Tab           = 258,
    Backspace     = 259,
    Insert        = 260,
    Delete        = 261,
    Right         = 262,
    Left          = 263,
    Down          = 264,
    Up            = 265,
    PageUp        = 266,
    PageDown      = 267,
    Home          = 268,
    End           = 269,
    CapsLock      = 280,
    ScrollLock    = 281,
    NumLock       = 282,
    PrintScreen   = 283,
    Pause         = 284,
    
    F1            = 290,
    F2            = 291,
    F3            = 292,
    F4            = 293,
    F5            = 294,
    F6            = 295,
    F7            = 296,
    F8            = 297,
    F9            = 298,
    F10           = 299,
    F11           = 300,
    F12           = 301,
    
    // Numpad
    KP_0          = 320,
    KP_1          = 321,
    KP_2          = 322,
    KP_3          = 323,
    KP_4          = 324,
    KP_5          = 325,
    KP_6          = 326,
    KP_7          = 327,
    KP_8          = 328,
    KP_9          = 329,
    KP_Decimal    = 330,
    KP_Divide     = 331,
    KP_Multiply   = 332,
    KP_Subtract   = 333,
    KP_Add        = 334,
    KP_Enter      = 335,
    KP_Equal      = 336,
    
    // Modifiers
    Left_Shift     = 340,
    Left_Control   = 341,
    Left_Alt       = 342,
    Left_Super     = 343, // Windows Key / Mac Command
    Right_Shift    = 344,
    Right_Control  = 345,
    Right_Alt      = 346,
    Right_Super    = 347
};