#ifndef RENDERER_CONFIG_HH
#define RENDERER_CONFIG_HH

#include <utility>

class renderer_config
{
public:
  renderer_config(int segment_length,
		float left_angle, float right_angle,
		float initial_angle,
		std::pair<float, float> translation = std::make_pair(0.0f, 0.0f),
		std::pair<float, float> scale = std::make_pair(1.0f, 1.0f))
    : segment_length_(segment_length),
      left_angle_(left_angle),
      right_angle_(right_angle),
      initial_angle_(initial_angle),
      translation_(translation),
      scale_(scale)
  {}

  int   segment_length() const { return segment_length_; }
  float left_angle()     const { return left_angle_; }
  float right_angle()    const { return right_angle_; }
  float initial_angle()  const { return initial_angle_; }

  std::pair<float, float> translation() const { return translation_; }
  std::pair<float, float> scale()       const { return scale_; }

private:
  int segment_length_;
  float left_angle_;
  float right_angle_;
  float initial_angle_;
  std::pair<float, float> translation_;
  std::pair<float, float> scale_;
};

#endif // RENDERER_CONFIG_HH
