#pragma once

class Patient
{
public:
	Patient() = default;
	Patient& cure();

private:
	bool m_cured = false;
};

