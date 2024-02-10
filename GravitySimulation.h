class GravitySimulation {

	private:
		float gravityVelocity;
		float airDrag;
	public:
		GravitySimulation(float gravityVelocity);
		GravitySimulation(float gravityVelocity, float airDrag);
		float getDistance(float seconds);
		float getDistance(float seconds, float mass);

};
