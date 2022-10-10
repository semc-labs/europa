// ======================================================================
// \title  PIDController.cpp
// \author codeflight1
// \brief  cpp file for PIDController component implementation class
// ======================================================================


#include <SignalProcessing/PIDController/PIDController.hpp>
#include <FpConfig.hpp>
#include <Fw/Types/Assert.hpp>

namespace SignalProcessing {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PIDController ::
    PIDController(
        const char *const compName
    ) : PIDControllerComponentBase(compName)
  {

  }

  void PIDController ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    PIDControllerComponentBase::init(instance);
  }


  void PIDController ::
    configure(
        F32 tau,
        F32 limMin,
        F32 limMax,
        F32 T
    )
  {
    this->tau = tau;
    this->limMin = limMin;
    this->limMin = limMax;
    this->T = T;
    this->configured = true;
  }

  void PIDController ::
    preamble()
  {
    FW_ASSERT(this->configured);
  }

  PIDController ::
    ~PIDController()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PIDController ::
    dataIn_handler(
        const NATIVE_INT_TYPE portNum,
        F32 setpoint,
        F32 measurement
    )
  {
    Fw::ParamValid valid;
    PIDGains gains = paramGet_Gains(valid);
    FW_ASSERT(valid == Fw::ParamValid::VALID);

    F32 error = setpoint - measurement;

    F32 proportional = gains.getKp() * error;

    this->integral += 0.5f * gains.getKi() * this->T * (error + this->prevError);

    // Anti-wind-up via dynamic integrator clamping
    F32 limMinInt, limMaxInt;

    // Compute integrator limits
    limMaxInt = (this->limMax > proportional) ? (this->limMax - proportional) : 0.0f;
    limMinInt = (this->limMin < proportional) ? (this->limMin - proportional) : 0.0f;

    // Clamp integrator
    if (this->integral > limMaxInt) {
        this->integral = limMaxInt;
    }else if (this->integral < limMinInt) {
        this->integral = limMinInt;
    }

    this->derivative = -(2.0f * gains.getKd() * (measurement - this->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * this->tau - this->T) * this->derivative)
                        / (2.0f * this->tau + this->T);

    this->out = proportional + this->integral + this->derivative;

    if (this->out > this->limMax) {
        this->out = this->limMax;
    }else if (this->out < this->limMin) {
        this->out = this->limMin;
    }

    this->prevError       = error;
    this->prevMeasurement = measurement;

    this->out_out(0, this->out);
  }

} // end namespace SignalProcessing
