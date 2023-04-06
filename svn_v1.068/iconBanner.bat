pushd .\

cd data\iconBanner\banner\cgb
"%CTRSDK_ROOT%"\tools\CommandLineTools\ctr_BannerModelConverter32 Banner

popd
pushd .\
cd data\iconBanner\banner\dmg
"%CTRSDK_ROOT%"\tools\CommandLineTools\ctr_BannerModelConverter32 Banner

popd
pushd .\

cd data\iconBanner\icon
"%CTRSDK_ROOT%"\tools\CommandLineTools\ctr_TexturePackager32 -dsl -l icon24.tga
"%CTRSDK_ROOT%"\tools\CommandLineTools\ctr_TexturePackager32 -dsl -l icon48.tga

popd
pushd .\

cd data\iconBanner\snd
"%CTRSDK_ROOT%"\tools\CommandLineTools\ctr_WaveConverter32 --pcm16 -o banner_snd.bcwav banner_snd.aif

popd
pause
