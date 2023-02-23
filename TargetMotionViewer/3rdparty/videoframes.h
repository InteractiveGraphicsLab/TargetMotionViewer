#pragma once




//
// class TVideoFrames
// Videoを保持するデータ構造
//
template<class T>
class TVideoFrames
{

public:
  int m_W, m_H, m_fNum;
  T **m_frms;

  TVideoFrames() {
    m_frms = 0;
    m_W = m_H = m_fNum = 0;
  }

  ~TVideoFrames() {
    clear();
  }

  TVideoFrames(const TVideoFrames& src) {
    m_frms = 0;
    m_W = m_H = m_fNum = 0;
    set(src);
  }

  TVideoFrames& operator=(const TVideoFrames& src) {
    m_frms = 0;
    m_W = m_H = m_fNum = 0;
    set(src);
  }

  void set(const TVideoFrames &src)
  {
    clear();

    m_W = src.m_W;
    m_H = src.m_H;
    m_fNum = src.m_fNum;

    m_frms = new T*[m_fNum];
    for (int i = 0; i < m_fNum; ++i)
    {
      m_frms[i] = new T[m_W * m_H];
      if (src.m_frms[i] != 0) memcpy(m_frms[i], src.m_frms[i], sizeof(T) * m_W * m_H);
    }
  }

  inline        T* operator[](int id) { return m_frms[id]; }
  inline  const T* operator[](int id) const { return m_frms[id]; }

  inline void allocate(const int W, const int H, const int fNum)
  {
    clear();

    m_W = W;
    m_H = H;
    m_fNum = fNum;

    m_frms = new T*[m_fNum];
    for (int i = 0; i < m_fNum; ++i)
    {
      m_frms[i] = new T[m_W * m_H];
      memset(m_frms[i], 0, sizeof(T)*W*H);
    }
  }

  void clear()
  {
    if (m_frms != 0)
    {
      for (int i = 0; i < m_fNum; ++i) delete[] m_frms[i];
      delete[] m_frms;
    }

    m_W = m_H = m_fNum = 0;
    m_frms = 0;
  }



  //
  //平均画像の計算
  //meanimage should be allocated
  //
  inline void CalcMeanImage(const int start_idx, const int frame_num, T *meanimage)
  {
    const int pixel_num = m_W * m_H;

    double *tmp = new double[pixel_num];
    memset(tmp, 0, sizeof(double) * pixel_num);

    for (int f = 0; f < frame_num; ++f)
      for (int i = 0; i < pixel_num; ++i)
        tmp[i] += (double)m_frms[start_idx + f][i];

    for (int i = 0; i < pixel_num; ++i)
      meanimage[i] = (T)(tmp[i] / frame_num);

    delete[] tmp;
  }

  inline void CalcMeanImage(T *meanimage)
  {
    CalcMeanImage(0, m_fNum, meanimage);
  }

};


