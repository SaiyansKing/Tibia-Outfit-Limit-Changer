Tibia Outfit Limit Changer
===============

Tibia Outfit Limit Changer is a tool that modifies old versions of Tibia Clients to allow them to use more than hardcoded 25 outfit limit.  
Currently only support 8.54 and 8.60 client versions, in future maybe there'll be more clients supported.  
If you want to use more than 255 outfits you need server-side changes to from "msg.addByte(protocolOutfits.size());" to "msg.add<uint16_t>(protocolOutfits.size());" in protocolgame.cpp

### Donation
If you like what I'm doing you can donate me :)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=jakubkubina@hotmail.com&rm=0&currency_code=USD)
