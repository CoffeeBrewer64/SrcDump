mkdir objects\brsrc
rm objects/brsrc/anim/*
rm objects/brsrc/blyt/*
rm objects/brsrc/timg/*
"%NW4C_ROOT%"\lyt1\tool\LayoutEditor\Converter\NW4C_LayoutConverter -g data\VCM\HomeNixSign\layout\layout_out objects\brsrc

rm objects/brsrc/font/*
pushd objects\brsrc
"%NW4C_ROOT%"\lyt1\tool\LayoutEditor\Converter\NW4C_LayoutArchiver -r *.bclim 128 -r *.bcfnt 128 -r *.bcfna 128 -a 4 -c ..\..\data\VCM\HomeNixSign\layout.arc .
popd