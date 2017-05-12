# Overview

Multiscribe is an add-on for Windows applications that enables text rendering in
complex scripts not otherwise supported by Windows. Multiscribe uses the Graphite
rendering engine developed by the Non Roman Script Initiative (NRSI) of SIL
International.

Multiscribe works by wrapping Uniscribe, the Windows complex font shaping engine, so
that any time an application would have called Uniscribe, the Graphite engine gets a
chance to do its work. The Graphite engine only works with Graphite fonts and the
rest are passed on to Uniscribe. Linux already has similar functionality in the form
of PangoGraphite.

## Installation Notes

### System Requirements

- Windows 2000/XP/NT or Vista (32 bit only).
- Any hardware that runs these operating systems is fine.
- Support for complex scripts must be turned on.

### Installation

There should be an installer.
