from enigma import eTimer
from Plugins.Plugin import PluginDescriptor
from Components.Console import Console

class OnErrorRestart:
	def __init__(self, session):
		self.Console = Console()
		self.session = session
		self.error = 0
		self.timercount = 0

	def StartLongTimer(self):
		print "[OnErrorRestartService] start long timer"
		self.Timer = eTimer()
		self.Timer.callback.append(self.checklog)
		self.Timer.start(1000*20, False)

	def StartFastTimer(self):
		print "[OnErrorRestartService] check error, start fast timer"
		self.Timer = eTimer()
		self.Timer.callback.append(self.checklog)
		self.Timer.start(1000*3, False)

	def checklog(self):
		self.Console.ePopen('dmesg -c | grep "Error-pti_task"' , self.checkerror)

	def checkerror(self, result, retval, extra_args):
		if result.strip():
			if self.error >= 1:
				print "[OnErrorRestartService] restart service"
				self.error = 0
				service = self.session.nav.getCurrentlyPlayingServiceOrGroup()
				if service:
					self.session.nav.stopService()
					self.session.nav.playService(service)
				self.ResetTimer()
			else:
				self.error += 1
				self.Timer.stop()
				self.timercount += 1
				self.StartFastTimer()
		elif self.timercount >= 0:
			if self.timercount <= 10:
				self.timercount += 1
			else:
				self.ResetTimer()

	def ResetTimer(self):
		self.timercount = 0
		self.error = 0
		self.Timer.stop()
		self.StartLongTimer()

ErrorCheckInstance = None

def main(session, **kwargs):
	global ErrorCheckInstance
	if ErrorCheckInstance is None:
		ErrorCheckInstance = OnErrorRestart(session)
		ErrorCheckInstance.StartLongTimer()

def Plugins(**kwargs):
	return [ PluginDescriptor(where = PluginDescriptor.WHERE_SESSIONSTART, fnc=main ) ]