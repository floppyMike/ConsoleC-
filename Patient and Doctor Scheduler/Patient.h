#pragma once

class Patient
{
public:
	Patient() = default;
	Patient& cure();
	bool cured() const noexcept;

private:
	bool m_cured = false;
};

