#include <stdint.h>
#include <sys/time.h>


#define MSR_TSC				0x10
#define MSR_NEHALEM_PLATFORM_INFO	0xCE
#define MSR_NEHALEM_TURBO_RATIO_LIMIT	0x1AD
#define MSR_APERF			0xE8
#define MSR_MPERF			0xE7
#define MSR_PKG_C3_RESIDENCY		0x3F8
#define MSR_PKG_C6_RESIDENCY		0x3F9
#define MSR_CORE_C3_RESIDENCY		0x3FC
#define MSR_CORE_C6_RESIDENCY		0x3FD


class nhm_package: public cpu_package 
{
private:
	uint64_t	c3_before, c3_after;
	uint64_t	c6_before, c6_after;
	uint64_t	tsc_before, tsc_after;

	uint64_t	last_stamp;
	uint64_t	total_stamp;

	void		account_freq(uint64_t frequency, uint64_t duration);

public:
	virtual void 	measurement_start(void);
	virtual void 	measurement_end(void);
	virtual int     can_collapse(void) { return 0;};

	virtual char *  fill_pstate_line(int line_nr, char *buffer);

	virtual void    calculate_freq(uint64_t time);
	virtual void	change_effective_frequency(uint64_t time, uint64_t freq);

	virtual void    report_out(void);

};

class nhm_core: public cpu_core 
{
private:
	uint64_t	c3_before, c3_after;
	uint64_t	c6_before, c6_after;
	uint64_t	tsc_before, tsc_after;

	uint64_t	last_stamp;
	uint64_t	total_stamp;

	void		account_freq(uint64_t frequency, uint64_t duration);
public:
	virtual void 	measurement_start(void);
	virtual void 	measurement_end(void);
	virtual int     can_collapse(void) { return 0;};

	virtual char *  fill_pstate_line(int line_nr, char *buffer);

	virtual void    calculate_freq(uint64_t time);
	virtual void	change_effective_frequency(uint64_t time, uint64_t freq);

	virtual void    report_out(void);

};

class nhm_cpu: public cpu_linux
{
private:
	uint64_t	aperf_before;
	uint64_t	aperf_after;
	uint64_t	mperf_before;
	uint64_t	mperf_after;
	uint64_t	tsc_before, tsc_after;

	uint64_t	last_stamp;
	uint64_t	total_stamp;

	void		account_freq(uint64_t frequency, uint64_t duration);
public:
	virtual void 	measurement_start(void);
	virtual void 	measurement_end(void);
	virtual int     can_collapse(void) { return 0;};

	virtual char *  fill_pstate_name(int line_nr, char *buffer);
	virtual char *  fill_pstate_line(int line_nr, char *buffer);
	virtual int	has_pstate_level(int level);

	virtual void    change_freq(uint64_t time, int freq);
	virtual void	change_effective_frequency(uint64_t time, uint64_t freq);
	virtual void    go_idle(uint64_t time);
	virtual void    go_unidle(uint64_t time);

};

class atom_package: public cpu_package 
{
public:
	virtual void 	measurement_start(void);
	virtual void 	measurement_end(void);

};

class atom_core: public cpu_core
{
public:
	virtual void 	measurement_start(void);
	virtual void 	measurement_end(void);

};

