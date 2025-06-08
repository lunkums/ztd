#ifndef ZTA_ASCII_H
#define ZTA_ASCII_H

#include "zta/types.h"

namespace zta { namespace ascii {
    /// The C0 control codes of the ASCII encoding.
    ///
    /// See also: https://en.wikipedia.org/wiki/C0_and_C1_control_codes and `isControl`
    namespace control_code {
        /// Null.
        const int nul = 0x00;
        /// Start of Heading.
        const int soh = 0x01;
        /// Start of Text.
        const int stx = 0x02;
        /// End of Text.
        const int etx = 0x03;
        /// End of Transmission.
        const int eot = 0x04;
        /// Enquiry.
        const int enq = 0x05;
        /// Acknowledge.
        const int ack = 0x06;
        /// Bell, Alert.
        const int bel = 0x07;
        /// Backspace.
        const int bs = 0x08;
        /// Horizontal Tab, Tab ('\t').
        const int ht = 0x09;
        /// Line Feed, Newline ('\n').
        const int lf = 0x0A;
        /// Vertical Tab.
        const int vt = 0x0B;
        /// Form Feed.
        const int ff = 0x0C;
        /// Carriage Return ('\r').
        const int cr = 0x0D;
        /// Shift Out.
        const int so = 0x0E;
        /// Shift In.
        const int si = 0x0F;
        /// Data Link Escape.
        const int dle = 0x10;
        /// Device Control One (XON).
        const int dc1 = 0x11;
        /// Device Control Two.
        const int dc2 = 0x12;
        /// Device Control Three (XOFF).
        const int dc3 = 0x13;
        /// Device Control Four.
        const int dc4 = 0x14;
        /// Negative Acknowledge.
        const int nak = 0x15;
        /// Synchronous Idle.
        const int syn = 0x16;
        /// End of Transmission Block
        const int etb = 0x17;
        /// Cancel.
        const int can = 0x18;
        /// End of Medium.
        const int em = 0x19;
        /// Substitute.
        const int sub = 0x1A;
        /// Escape.
        const int esc = 0x1B;
        /// File Separator.
        const int fs = 0x1C;
        /// Group Separator.
        const int gs = 0x1D;
        /// Record Separator.
        const int rs = 0x1E;
        /// Unit Separator.
        const int us = 0x1F;

        /// Delete.
        const int del = 0x7F;

        /// An alias to `dc1`.
        const int xon = dc1;
        /// An alias to `dc3`.
        const int xoff = dc3;
    }

    bool is_upper(u8 c);

    u8 to_lower(u8 c);
}}

#endif
