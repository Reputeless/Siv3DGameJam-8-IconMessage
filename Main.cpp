# include <Siv3D.hpp>

void Main()
{
	const Image fontImage(L"font.png");

	if (!fontImage)
	{
		return;
	}

	const String chars = L" ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::unordered_map<wchar, std::array<std::array<bool, 5>, 7>> fonts;
	
	for (auto c : step(chars.length))
	{
		std::array<std::array<bool, 5>, 7> font;

		for (auto p : step({ 5, 7 }))
		{
			font[p.y][p.x] = fontImage[c * 8 + p.y][p.x].r != 0;
		}

		fonts.emplace(chars[c], font);
	}

	const String message = L" GAME OVER ";

	Grid<bool> output(message.length * 6, 7);

	for (auto c : step(message.length))
	{
		for (auto p : step({ 5, 7 }))
		{
			output[p.y][c * 6 + p.x] = fonts[message[c]][p.y][p.x];
		}
	}

	Image image(256, 256, Palette::Black);

	size_t offset = 0;

	while (System::Update())
	{
		if (System::FrameCount() % 10 == 0)
		{
			image.fill(Palette::Black);

			for (auto p : step({ 9, 7 }))
			{
				if (output[p.y][(p.x + offset) % (message.length * 6)])
				{
					Circle(p * 27 + Point(18, 45), 12).overwrite(image, Color(50, 220, 20));
				}
			}

			Window::SetIcon(image);

			++offset;
		}
	}
}
