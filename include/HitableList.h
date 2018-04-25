#pragma once

class HitableList : public IHitable
{
public:
	HitableList() {}
	HitableList(IHitable **l, uint32_t n)
		: m_List(l)
		, m_ListSize(n)
	{
	}
	~HitableList()
	{
		for (uint32_t i = 0; i < m_ListSize; ++i)
			delete m_List[i];

		m_List = nullptr;
	}

	IHitable** m_List;
	uint32_t m_ListSize;

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

};