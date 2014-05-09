####################
#Interface Classes
####################

#Borrowed from http://metabates.com/2011/02/07/building-interfaces-and-abstract-classes-in-ruby/
module AbstractInterface
  class InterfaceNotImplementedError < NoMethodError
  end

  def initialize()
    raise Exception.new("Cannot initialize an Animal abstract class")
  end

  def self.included(klass)
    klass.send(:include, AbstractInterface::Methods)
    klass.send(:extend, AbstractInterface::Methods)
  end

  module Methods
    def api_not_implemented(klass)
      caller.first.match(/in \`(.+)\'/)
      method_name = $1
      raise AbstractInterface::InterfaceNotImplementedError.new("#{klass.class.name} needs to implement '#{method_name}' for interface #{self.name}!")
    end

  end
end

class Car
  include AbstractInterface

  @@globalOptions = {
    :wheels => {:cost => 12000.00, :desc => "4 wheels"},
    :doors => {:cost => 2000.00, :desc => "2 doors"},
    :ac => {:cost => 1500.00, :desc => "AC"},
    :sound => {:cost => 1000.00, :desc => "premium sound system"},
    :navigation => {:cost => 2000.00, :desc => "navigation"},
    :automatic_transmission => {:cost => 3000.00, :desc => "automatic transmission"},
    :manual_transmission => {:cost => 2500.00, :desc => "manual transmission"},
    :v8 => {:cost => 6000.00, :desc => "V8"},
    :super_charger => {:cost => 3000.00, :desc => "super-charger"}
  }

  def cost
    cost = 0.0
    @options.each do |option|
      cost += @@globalOptions[option][:cost]
    end

    return cost
  end

  def description
    description = "#{@name} with "
    listOfDescriptions = []
    options.each do |option|
      listOfDescriptions.push(@@globalOptions[option])
    end

    description = description + listOfDescriptions.join(",")
    return description
  end
end 

########################
# Classes
########################

class RunAbout < Car
  def initialize()
    @name = "RunAbout"
    @options = [:wheels, :doors]
  end
end

class SUV < Car
  def initialize()
    @name = "SUV"
    @options = [:wheels, :doors, :ac, :automatic_transmission]
  end
end

class Status < Car
  def initialize()
    @name = "Status"
    @options = [:wheels, :doors, :ac, :sound, 
      :navigation, :automatic_transmission]
  end
end

class Performance < Car
  def initialize()
    @name = "Performance"
    @options = [:wheels, :doors, :ac, :sound, 
      :navigation, :manual_transmission, :v8, :super_scharger]
  end
end

########################
# Methods
########################

def demo()
  puts "<< Hello Decorator Problem >>"
end

########################
# Main
########################

demo()