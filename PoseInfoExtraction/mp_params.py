import mediapipe as mp
mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose
mp_holistic = mp.solutions.holistic

POINT_NAME = [
    mp_holistic.PoseLandmark.NOSE,            mp_holistic.PoseLandmark.LEFT_EYE_INNER,
    mp_holistic.PoseLandmark.LEFT_EYE,        mp_holistic.PoseLandmark.LEFT_EYE_OUTER,
    mp_holistic.PoseLandmark.RIGHT_EYE_INNER, mp_holistic.PoseLandmark.RIGHT_EYE,
    mp_holistic.PoseLandmark.RIGHT_EYE_OUTER, mp_holistic.PoseLandmark.LEFT_EAR,
    mp_holistic.PoseLandmark.RIGHT_EAR,       mp_holistic.PoseLandmark.MOUTH_LEFT,
    mp_holistic.PoseLandmark.MOUTH_RIGHT,     mp_holistic.PoseLandmark.LEFT_SHOULDER,
    mp_holistic.PoseLandmark.RIGHT_SHOULDER,  mp_holistic.PoseLandmark.LEFT_ELBOW,
    mp_holistic.PoseLandmark.RIGHT_ELBOW,     mp_holistic.PoseLandmark.LEFT_WRIST,
    mp_holistic.PoseLandmark.RIGHT_WRIST,     mp_holistic.PoseLandmark.LEFT_PINKY,
    mp_holistic.PoseLandmark.RIGHT_PINKY,     mp_holistic.PoseLandmark.LEFT_INDEX,
    mp_holistic.PoseLandmark.RIGHT_INDEX,     mp_holistic.PoseLandmark.LEFT_THUMB,
    mp_holistic.PoseLandmark.RIGHT_THUMB,     mp_holistic.PoseLandmark.LEFT_HIP,
    mp_holistic.PoseLandmark.RIGHT_HIP,       mp_holistic.PoseLandmark.LEFT_KNEE,
    mp_holistic.PoseLandmark.RIGHT_KNEE,      mp_holistic.PoseLandmark.LEFT_ANKLE,
    mp_holistic.PoseLandmark.RIGHT_ANKLE,     mp_holistic.PoseLandmark.LEFT_HEEL,
    mp_holistic.PoseLandmark.RIGHT_HEEL,      mp_holistic.PoseLandmark.LEFT_FOOT_INDEX,
    mp_holistic.PoseLandmark.RIGHT_FOOT_INDEX]

COLORs = [
( 0, 0,255),( 0,255, 0),(255, 0, 0),(255,255, 0),(255, 0,255),( 0,255,255),
( 0, 0,128),( 0,128, 0),(128, 0, 0),(128,128, 0),(128, 0,128),( 0,128,128),
( 0, 0, 64),( 0, 64, 0),( 64, 0, 0),( 64, 64, 0),( 64, 0, 64),( 0, 64, 64),
(64,64,255),(64,255,64),(255,64,64),(255,255,64),(255,64,255),(64,255,255),
(64,64,128),(64,128,64),(128,64,64),(128,128,64),(128,64,128),(64,128,128),
(255,128,128),(128,255,128), (128,128,255)]
